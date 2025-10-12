@echo off

set DEP=%TEMP%\ts_dep
set DEP_SRC="%DEP%.cpp"

if not exist "%DEP%.exe" (
	if not defined VSCOMNTOOLS (
		call "%~dp0\vcvars_any.bat"
	)
	more +19 "%~dp0\ts_dep.bat" > "%DEP_SRC%"
	cl.exe /nologo /MD /Os /EHsc /c "%DEP_SRC%" /Fo"%DEP%.obj"
	link.exe /nologo /out:"%DEP%.exe" "%DEP%.obj"
	del "%DEP_SRC%" "%DEP%.obj"
)

call "%DEP%.exe" %*

goto :eof

#include <set>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;
int main(int argc, char **argv) {
	set<string> paths;
	vector<string> inputs;
	ostream *out = &cout;
	const char *output = nullptr;
	for(int i = 1; i < argc; i++) {
		const char *s = argv[i];
		if(*s == '/') {
			if(s[1] == 'I') {
				string path;
				for(s += 2; *s; s++) path += (*s == '/' ? '\\' : *s);
				if(path.back() != '\\') path += "\\";
				paths.insert(path);
			} else if(s[1] == 'F' && s[2] == 'o') {
				output = s + 3;
			}
			else cerr << "unknown option: " << s << endl;
			continue;
		}
		inputs.push_back(string(s));
	}
	ofstream fout;
	if(output && inputs.size()) {
		fout.open(output);
		out = &fout;
	}
	string line, name;
	string root, include;
	const char *names[] = {
		"include\\", "plugins\\", nullptr,
	};
	const char *tsroot = getenv("TSROOT");
	for(size_t i = 0; i < inputs.size(); i++) {
		vector<string> includes;
		map<string, string> depends;
		includes.push_back(inputs[i]);
		for(size_t j = 0; j < includes.size(); j++) {
			fstream file;
			root.clear();
			include.clear();
			name = includes[j];
			file.open(name);
			for(int k = 0; !file && k <= 8; k++) {
				for(int l = 0; !file && names[l]; l++) {
					name = root + names[l] + includes[j];
					file.open(name);
				}
				root += "..\\";
			}
			for(int k = 0; !file && tsroot && names[k]; k++) {
				root = string(tsroot) + "\\";
				name = root + names[k] + includes[j];
				file.open(name);
			}
			for(auto it = paths.begin(); !file && it != paths.end(); ++it) {
				name = *it + includes[j];
				file.open(name);
			}
			if(!file) name.clear();
			for(const char *s = name.c_str(); *s; s++) {
				size_t pos = include.rfind("..\\");
				if(include.size() && pos + 3 != include.size() && *s == '.' && s[1] == '.' && s[2] == '\\') {
					include.pop_back();
					while(include.size() && include.back() != '\\') include.pop_back();
					s += 2;
				} else {
					include += *s;
				}
			}
			depends[includes[j]] = include;
			if(!file) continue;
			while(file) {
				getline(file, line);
				const char *s = line.c_str();
				while(*s == ' ' || *s == '\t') s++;
				if(strncmp(s, "#include", 8)) continue;
				s += 8;
				while(*s == ' ' || *s == '\t') s++;
				if(*s == '<' || *s == '"') s++;
				for(include.clear(); *s && *s != '>' && *s != '"'; s++) include += (*s == '/' ? '\\' : *s);
				if(depends.find(include) != depends.end()) continue;
				if(*s == '"') {
					size_t pos = name.rfind("\\");
					if(pos < name.size()) paths.insert(name.substr(0, pos + 1));
				}
				includes.push_back(include);
				depends[include] = include;
			}
		}
		if(depends.size() < 2) continue;
		auto it = depends.find(inputs[i]);
		if(!it->second.size()) continue;
		*out << inputs[i];
		if(inputs[i] != it->second) *out << " " << it->second;
		*out << ": \\" << endl;
		for(auto it = depends.begin(); it != depends.end();) {
			*out << "\t";
			for(size_t j = 0; j < 160 && it != depends.end(); ++it) {
				if(j && j + it->second.size() >= 160) break;
				if(inputs[i] == it->first) continue;
				if(!it->second.size()) continue;
				*out << it->second << " ";
				j += it->second.size();
			}
			*out << (it != depends.end() ? "\\" : "") << endl;
		}
	}
	return 0;
}
