// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <core/TellusimSort.h>
#include <format/TellusimXml.h>
#include <geometry/TellusimBounds.h>

#include <interface/tooltip/include/TellusimControlTooltip.h>
#include "../include/TellusimControlFlow.h"

/*
 */
namespace Tellusim {
	
	/*
	 */
	static const char *control_flow_shape_names[] = {
		"circle", "hexagon", "pentagon", "square", "diamond", "triangle", "arrow",
		"ring", "frame", "delta", "nabla", "equal", "cross", "plus", "hash", "star",
	};
	TS_STATIC_ASSERT(TS_COUNTOF(control_flow_shape_names) == ControlFlow::NumShapes);
	
	/*
	 */
	ControlFlow::ControlFlow(Control *parent, const char *variant, uint32_t version) : ControlBase(parent), variant(variant), version(version) {
		
		// selection style
		setSelectionStyle(StrokeStyle(3.0f, Color(0.6f, 0.8f, 1.0f, 0.75f)));
		
		// proto style
		setProtoColor(Color(0.7f, 0.8f));
		setProtoStrokeStyle(StrokeStyle(3.0f, Color::black));
		setProtoGradientStyle(GradientStyle(1.7f, Vector2f(0.2f, 1.0f), Color::gray, Color::black));
	}
	
	ControlFlow::~ControlFlow() {
		
	}
	
	/*
	 */
	void ControlFlow::clearFlow() {
		clearNodes();
		clearProtos();
		clearTypes();
	}
	
	/*
	 */
	void ControlFlow::load_stroke_style(const Xml &xml, StrokeStyle &style) {
		if(xml.getName() == "stroke") {
			for(const Xml &child : xml.getChildren()) {
				const String &name = child.getName();
				if(name == "width") style.width = child.getDataf32();
				if(name == "offset") style.offset = child.getDataf32();
				if(name == "color") child.getData(style.color.c, 4);
			}
		}
	}
	
	void ControlFlow::load_gradient_style(const Xml &xml, GradientStyle &style) {
		if(xml.getName() == "gradient") {
			for(const Xml &child : xml.getChildren()) {
				const String &name = child.getName();
				if(name == "radius") style.radius = child.getDataf32();
				if(name == "length") style.length = child.getDataf32();
				if(name == "center") child.getData(style.center.v, 2);
				if(name == "axis") child.getData(style.axis.v, 2);
				if(name == "color_0") child.getData(style.color_0.c, 4);
				if(name == "color_1") child.getData(style.color_1.c, 4);
			}
		}
	}
	
	/*
	 */
	void ControlFlow::save_stroke_style(Xml &xml, const StrokeStyle &style) {
		Xml child = Xml(&xml, "stroke");
		if(style.width != 0.0f) child.setData("width", style.width);
		if(style.offset != 0.0f) child.setData("offset", style.offset);
		if(style.color != Color::white) child.setData("color", style.color.c, 4);
	}
	
	void ControlFlow::save_gradient_style(Xml &xml, const GradientStyle &style) {
		Xml child = Xml(&xml, "gradient");
		if(style.radius != 0.0f) child.setData("radius", style.radius);
		if(style.length != 0.0f) child.setData("length", style.length);
		if(style.center != Vector2f::zero) child.setData("center", style.center.v, 2);
		if(style.axis != Vector2f::zero) child.setData("axis", style.axis.v, 2);
		if(style.color_0 != Color::white) child.setData("color_0", style.color_0.c, 4);
		if(style.color_1 != Color::black) child.setData("color_1", style.color_1.c, 4);
	}
	
	/*
	 */
	bool ControlFlow::load(const Xml &parent, bool merge) {
		
		// clear flow
		if(!merge) clearFlow();
		
		// flow root
		const Xml xml = parent.getChild("flow");
		if(!xml) return false;
		
		// flow variant
		variant = xml.getAttribute("variant");
		version = xml.getAttribute("version", 0);
		
		// types merge
		Map<uint32_t, uint32_t> type_indices;
		
		// protos merge
		struct ProtoIndices {
			uint32_t proto_index;
			Map<uint32_t, uint32_t> input_indices;
			Map<uint32_t, uint32_t> output_indices;
		};
		Map<uint32_t, ProtoIndices> proto_indices;
		
		// node indices
		struct NodeIndices {
			uint32_t node_index;
			uint32_t proto_index;
		};
		Map<uint32_t, NodeIndices> node_indices;
		
		// collapsed indices
		Array<uint32_t> collapsed_indices;
		
		// control parameters
		float32_t loaded_scale = 1.0f;
		loaded_position = Vector2f::zero;
		Vector2f loaded_size = Vector2f::zero;
		
		// load flow
		for(const Xml &child : xml.getChildren()) {
			const String &name = child.getName();
			
			// control parameters
			if(name == "controls") {
				for(const Xml &control_xml : child.getChildren()) {
					const String &name = control_xml.getName();
					if(name == "position") control_xml.getData(loaded_position.v, 2);
					else if(name == "scale") loaded_scale = control_xml.getDataf32();
					else TS_LOGF(Warning, "ControlFlow::load(): unknown type node \"%s\"\n", name.get());
				}
			}
			
			// load types
			else if(name == "types") {
				reserveTypes(child.getNumChildren());
				for(const Xml &types_xml : child.getChildren()) {
					const String &name = types_xml.getName();
					if(name == "type") {
						const String &name = types_xml.getAttribute("name");
						uint32_t src_index = types_xml.getAttribute("index", Maxu32);
						uint32_t type_index = findType(name);
						if(type_index == Maxu32) {
							type_index = addType(name);
							type_indices.append(src_index, type_index);
							for(const Xml &type_xml : types_xml.getChildren()) {
								const String &name = type_xml.getName();
								if(name == "text") setTypeText(type_index, type_xml.getData());
								else if(name == "info") setTypeInfo(type_index, type_xml.getData());
								else if(name == "value") setTypeValue(type_index, type_xml.getData());
								else if(name == "color") type_xml.getData(types[type_index].color.c, 4);
								else if(name == "stroke") load_stroke_style(type_xml, types[type_index].stroke_style);
								else if(name == "gradient") load_gradient_style(type_xml, types[type_index].gradient_style);
								else if(name == "edit") setTypeEditMode(type_index, (ControlEdit::EditMode)type_xml.getDatau32());
								else if(name == "mask" || name == "input" || name == "output") {
									TypeMask mask;
									Array<String> masks(64u);
									masks.resize(type_xml.getData(masks));
									for(const String &name : masks) {
										uint32_t index = findType(name);
										if(index < TypeMask::NumTypes) mask.set(index);
										else if(index != Maxu32) TS_LOGF(Warning, "ControlFlow::load(): can't apply mask for \"%s\"\n", name.get());
										else TS_LOGF(Warning, "ControlFlow::load(): unknown type \"%s\"\n", name.get());
									}
									if(name == "mask" || name == "input") setTypeInputMask(type_index, mask);
									if(name == "mask" || name == "output") setTypeOutputMask(type_index, mask);
								}
								else if(name == "shape") {
									Shape shape = NumShapes;
									const String &name = type_xml.getData();
									for(uint32_t i = 0; i < NumShapes; i++) {
										if(control_flow_shape_names[i] == name) {
											shape = (Shape)i;
											break;
										}
									}
									if(shape < NumShapes) setTypeShape(type_index, shape);
									else TS_LOGF(Warning, "ControlFlow::load(): unknown shape \"%s\"\n", name.get());
								}
								else if(name == "connection") {
									for(const Xml &connection_xml : type_xml.getChildren()) {
										const String &name = connection_xml.getName();
										if(name == "width") setTypeConnectionWidth(type_index, connection_xml.getDataf32());
										else if(name == "color") connection_xml.getData(types[type_index].connection_color.c, 4);
										else if(name == "stroke") load_stroke_style(connection_xml, types[type_index].connection_style);
										else TS_LOGF(Warning, "ControlFlow::load(): unknown connection node \"%s\"\n", name.get());
									}
								}
								else {
									TS_LOGF(Warning, "ControlFlow::load(): unknown type node \"%s\"\n", name.get());
								}
							}
						} else {
							type_indices.append(src_index, type_index);
						}
					}
					else {
						TS_LOGF(Warning, "ControlFlow::load(): unknown types node \"%s\"\n", name.get());
					}
				}
			}
			
			// load protos
			else if(name == "protos") {
				reserveProtos(child.getNumChildren());
				for(const Xml &protos_xml : child.getChildren()) {
					const String &name = protos_xml.getName();
					if(name == "proto") {
						const String &name = protos_xml.getAttribute("name");
						uint32_t src_index = protos_xml.getAttribute("index", Maxu32);
						uint32_t proto_index = findProto(name);
						if(proto_index == Maxu32) {
							proto_index = addProto(name);
							auto proto_indices_it = proto_indices.append(src_index);
							proto_indices_it->data.proto_index = proto_index;
							for(const Xml &proto_xml : protos_xml.getChildren()) {
								const String &name = proto_xml.getName();
								if(name == "text") setProtoText(proto_index, proto_xml.getData());
								else if(name == "info") setProtoInfo(proto_index, proto_xml.getData());
								else if(name == "title") setProtoTitle(proto_index, proto_xml.getData());
								else if(name == "value") setProtoValue(proto_index, proto_xml.getData());
								else if(name == "state") setProtoState(proto_index, proto_xml.getData());
								else if(name == "color") proto_xml.getData(protos[proto_index].color.c, 4);
								else if(name == "stroke") load_stroke_style(proto_xml, protos[proto_index].stroke_style);
								else if(name == "gradient") load_gradient_style(proto_xml, protos[proto_index].gradient_style);
								else if(name == "inputs") {
									for(const Xml &inputs_xml : proto_xml.getChildren()) {
										const String &name = inputs_xml.getName();
										if(name == "input") {
											uint32_t type_index = inputs_xml.getAttribute("type", Maxu32);
											auto type_it = type_indices.find(type_index);
											if(!type_it) {
												TS_LOGF(Warning, "ControlFlow::load(): unknown input type %u\n", type_index);
												continue;
											}
											uint32_t src_index = inputs_xml.getAttribute("index", Maxu32);
											uint32_t input_index = addProtoInput(proto_index, "", type_it->data);
											proto_indices_it->data.input_indices.append(src_index, input_index);
											for(const Xml &input_xml : inputs_xml.getChildren()) {
												const String &name = input_xml.getName();
												if(name == "name") setProtoInputName(proto_index, input_index, input_xml.getData());
												else if(name == "text") setProtoInputText(proto_index, input_index, input_xml.getData());
												else if(name == "info") setProtoInputInfo(proto_index, input_index, input_xml.getData());
												else if(name == "value") setProtoInputValue(proto_index, input_index, input_xml.getData());
												else if(name == "multi") setProtoMultiInput(proto_index, input_index, input_xml.getDataBool());
												else if(name == "final") setProtoFinalInput(proto_index, input_index, input_xml.getDataBool());
												else if(name == "separator") setProtoSeparatorInput(proto_index, input_index, input_xml.getDataBool());
												else TS_LOGF(Warning, "ControlFlow::load(): unknown input node \"%s\"\n", name.get());
											}
										}
										else {
											TS_LOGF(Warning, "ControlFlow::load(): unknown inputs node \"%s\"\n", name.get());
										}
									}
								}
								else if(name == "outputs") {
									for(const Xml &outputs_xml : proto_xml.getChildren()) {
										const String &name = outputs_xml.getName();
										if(name == "output") {
											uint32_t type_index = outputs_xml.getAttribute("type", Maxu32);
											auto type_it = type_indices.find(type_index);
											if(!type_it) {
												TS_LOGF(Warning, "ControlFlow::load(): unknown output type %u\n", type_index);
												continue;
											}
											uint32_t src_index = outputs_xml.getAttribute("index", Maxu32);
											uint32_t output_index = addProtoOutput(proto_index, "", type_it->data);
											proto_indices_it->data.output_indices.append(src_index, output_index);
											for(const Xml &output_xml : outputs_xml.getChildren()) {
												const String &name = output_xml.getName();
												if(name == "name") setProtoOutputName(proto_index, output_index, output_xml.getData());
												else if(name == "text") setProtoOutputText(proto_index, output_index, output_xml.getData());
												else if(name == "info") setProtoOutputInfo(proto_index, output_index, output_xml.getData());
												else if(name == "value") setProtoOutputValue(proto_index, output_index, output_xml.getData());
												else if(name == "multi") setProtoMultiOutput(proto_index, output_index, output_xml.getDataBool());
												else if(name == "final") setProtoFinalOutput(proto_index, output_index, output_xml.getDataBool());
												else if(name == "separator") setProtoSeparatorOutput(proto_index, output_index, output_xml.getDataBool());
												else TS_LOGF(Warning, "ControlFlow::load(): unknown output node \"%s\"\n", name.get());
											}
										}
										else {
											TS_LOGF(Warning, "ControlFlow::load(): unknown outputs node \"%s\"\n", name.get());
										}
									}
								}
								else {
									TS_LOGF(Warning, "ControlFlow::load(): unknown proto node \"%s\"\n", name.get());
								}
							}
						}
						// merge proto
						else {
							auto proto_indices_it = proto_indices.append(src_index);
							proto_indices_it->data.proto_index = proto_index;
							for(const Xml &proto_xml : protos_xml.getChildren()) {
								const String &name = proto_xml.getName();
								if(name == "inputs") {
									for(const Xml &inputs_xml : proto_xml.getChildren()) {
										const String &name = inputs_xml.getName();
										if(name == "input") {
											auto type_it = type_indices.end();
											uint32_t type_index = inputs_xml.getAttribute("type", Maxu32);
											if(type_index != Maxu32) {
												type_it = type_indices.find(type_index);
												if(!type_it) {
													TS_LOGF(Warning, "ControlFlow::load(): unknown input type %u\n", type_index);
													continue;
												}
											}
											String name = inputs_xml.getData("name");
											if(!name) name = inputs_xml.getData("text");
											if(!name && type_it) name = getTypeName(type_it->data);
											uint32_t input_index = findProtoInput(proto_index, name);
											if(input_index == Maxu32) {
												TS_LOGF(Warning, "ControlFlow::load(): unknown proto \"%s\" input \"%s\"\n", getProtoName(proto_index).get(), name.get());
												continue;
											}
											if(type_it && getProtoInputType(proto_index, input_index) != type_it->data) {
												TS_LOGF(Warning, "ControlFlow::load(): invalid proto \"%s\" input type \"%s\"\n", getProtoName(proto_index).get(), name.get());
											}
											uint32_t src_index = inputs_xml.getAttribute("index", Maxu32);
											proto_indices_it->data.input_indices.append(src_index, input_index);
										}
										else {
											TS_LOGF(Warning, "ControlFlow::load(): unknown inputs node \"%s\"\n", name.get());
										}
									}
								}
								else if(name == "outputs") {
									for(const Xml &outputs_xml : proto_xml.getChildren()) {
										const String &name = outputs_xml.getName();
										if(name == "output") {
											auto type_it = type_indices.end();
											uint32_t type_index = outputs_xml.getAttribute("type", Maxu32);
											if(type_index != Maxu32) {
												type_it = type_indices.find(type_index);
												if(!type_it) {
													TS_LOGF(Warning, "ControlFlow::load(): unknown output type %u\n", type_index);
													continue;
												}
											}
											String name = outputs_xml.getData("name");
											if(!name) name = outputs_xml.getData("text");
											if(!name && type_it) name = getTypeName(type_it->data);
											uint32_t output_index = findProtoOutput(proto_index, name);
											if(output_index == Maxu32) {
												TS_LOGF(Warning, "ControlFlow::load(): unknown proto \"%s\" output \"%s\"\n", getProtoName(proto_index).get(), name.get());
												continue;
											}
											if(type_it && getProtoOutputType(proto_index, output_index) != type_it->data) {
												TS_LOGF(Warning, "ControlFlow::load(): invalid proto \"%s\" output type \"%s\"\n", getProtoName(proto_index).get(), name.get());
											}
											uint32_t src_index = outputs_xml.getAttribute("index", Maxu32);
											proto_indices_it->data.output_indices.append(src_index, output_index);
										}
										else {
											TS_LOGF(Warning, "ControlFlow::load(): unknown outputs node \"%s\"\n", name.get());
										}
									}
								}
							}
						}
					}
					else {
						TS_LOGF(Warning, "ControlFlow::load(): unknown protos node \"%s\"\n", name.get());
					}
				}
			}
			
			// load nodes
			else if(name == "nodes") {
				reserveNodes(child.getNumChildren());
				for(const Xml &nodes_xml : child.getChildren()) {
					const String &name = nodes_xml.getName();
					if(name == "node") {
						uint32_t proto_index = nodes_xml.getAttribute("proto", Maxu32);
						auto proto_it = proto_indices.find(proto_index);
						if(!proto_it) {
							TS_LOGF(Warning, "ControlFlow::load(): unknown proto type %u\n", proto_index);
							continue;
						}
						uint32_t src_index = nodes_xml.getAttribute("index", Maxu32);
						uint32_t node_index = addNode(proto_it->data.proto_index);
						auto node_index_it = node_indices.append(src_index);
						node_index_it->data.node_index = node_index;
						node_index_it->data.proto_index = proto_index;
						for(const Xml &node_xml : nodes_xml.getChildren()) {
							const String &name = node_xml.getName();
							if(name == "value") setNodeValue(node_index, node_xml.getData());
							else if(name == "state") setNodeState(node_index, node_xml.getData());
							else if(name == "static") setNodeStatic(node_index, node_xml.getDataBool());
							else if(name == "dynamic") setNodeDynamic(node_index, node_xml.getDataBool());
							else if(name == "expanded") {
								if(!node_xml.getDataBool()) collapsed_indices.append(node_index);
							}
							else if(name == "position") {
								Vector2f position = Vector2f::zero;
								if(node_xml.getData(position.v, 2) == 2) setNodePosition(node_index, position);
								loaded_size = max(loaded_size, max(abs(position), Vector2f(128.0f)));
							}
							else if(name == "input") {
								uint32_t input_index = node_xml.getAttribute("index", Maxu32);
								auto input_it = proto_it->data.input_indices.find(input_index);
								if(!input_it) {
									TS_LOGF(Warning, "ControlFlow::load(): unknown input node index %u\n", input_index);
									continue;
								}
								if(node_xml.isAttribute("type")) {
									uint32_t type_index = node_xml.getAttribute("type", Maxu32);
									auto type_it = type_indices.find(type_index);
									if(!type_it) {
										TS_LOGF(Warning, "ControlFlow::load(): unknown input node type %u\n", type_index);
										continue;
									}
									setInputType(node_index, input_it->data, type_it->data);
								}
								for(const Xml &input_xml : node_xml.getChildren()) {
									const String &name = input_xml.getName();
									if(name == "value") setInputValue(node_index, input_it->data, input_xml.getData());
									else TS_LOGF(Warning, "ControlFlow::load(): unknown input node \"%s\"\n", name.get());
								}
							}
							else if(name == "output") {
								uint32_t output_index = node_xml.getAttribute("index", Maxu32);
								auto output_it = proto_it->data.output_indices.find(output_index);
								if(!output_it) {
									TS_LOGF(Warning, "ControlFlow::load(): unknown output node index %u\n", output_index);
									continue;
								}
								if(node_xml.isAttribute("type")) {
									uint32_t type_index = node_xml.getAttribute("type", Maxu32);
									auto type_it = type_indices.find(type_index);
									if(!type_it) {
										TS_LOGF(Warning, "ControlFlow::load(): unknown output node type %u\n", type_index);
										continue;
									}
									setOutputType(node_index, output_it->data, type_it->data);
								}
								for(const Xml &output_xml : node_xml.getChildren()) {
									const String &name = output_xml.getName();
									if(name == "value") setOutputValue(node_index, output_it->data, output_xml.getData());
									else TS_LOGF(Warning, "ControlFlow::load(): unknown output node \"%s\"\n", name.get());
								}
							}
						}
						const NodePtr &node = nodes[node_index];
						if(node->load_func) node->load_func(this, &nodes_xml, node_index);
						if(node->create_func) node->create_func(this, node_index);
					}
					else {
						TS_LOGF(Warning, "ControlFlow::load(): unknown nodes node \"%s\"\n", name.get());
					}
				}
			}
			
			// load connections
			else if(name == "connections") {
				for(const Xml &connections_xml : child.getChildren()) {
					const String &name = connections_xml.getName();
					if(name == "output") {
						uint32_t output_node = connections_xml.getAttribute("node", Maxu32);
						auto output_node_it = node_indices.find(output_node);
						if(!output_node_it) {
							TS_LOGF(Warning, "ControlFlow::load(): unknown output node %u\n", output_node);
							continue;
						}
						auto output_proto_it = proto_indices.find(output_node_it->data.proto_index);
						if(!output_proto_it) {
							TS_LOGF(Warning, "ControlFlow::load(): unknown output proto %u\n", output_node);
							continue;
						}
						uint32_t output_index = connections_xml.getAttribute("index", Maxu32);
						auto output_it = output_proto_it->data.output_indices.find(output_index);
						if(!output_it) {
							TS_LOGF(Warning, "ControlFlow::load(): unknown output index %u\n", output_index);
							continue;
						}
						for(const Xml &output_xml : connections_xml.getChildren()) {
							const String &name = output_xml.getName();
							if(name == "input") {
								uint32_t input_node = output_xml.getAttribute("node", Maxu32);
								auto input_node_it = node_indices.find(input_node);
								if(!input_node_it) {
									TS_LOGF(Warning, "ControlFlow::load(): unknown input node %u\n", input_node);
									continue;
								}
								auto input_proto_it = proto_indices.find(input_node_it->data.proto_index);
								if(!input_proto_it) {
									TS_LOGF(Warning, "ControlFlow::load(): unknown input proto %u\n", input_node);
									continue;
								}
								uint32_t input_index = output_xml.getAttribute("index", Maxu32);
								auto input_it = input_proto_it->data.input_indices.find(input_index);
								if(!input_it) {
									TS_LOGF(Warning, "ControlFlow::load(): unknown input index %u\n", input_index);
									continue;
								}
								addOutputConnection(output_node_it->data.node_index, output_it->data, input_node_it->data.node_index, input_it->data);
							}
							else {
								TS_LOGF(Warning, "ControlFlow::load(): unknown outputs node \"%s\"\n", name.get());
							}
						}
					}
					else {
						TS_LOGF(Warning, "ControlFlow::load(): unknown connections node \"%s\"\n", name.get());
					}
				}
			}
			else {
				TS_LOGF(Warning, "ControlFlow::load(): unknown node \"%s\"\n", name.get());
			}
		}
		
		// control parameters
		if(isCreated()) {
			flow_panel.setSize(max(flow_panel.getSize(), floor(loaded_size) * 16.0f));
			flow_area.setScale(loaded_scale);
		}
		
		// collapse nodes
		expand_nodes(collapsed_indices);
		
		// changed flag
		is_changed = true;
		
		// loaded flag
		is_loaded = true;
		
		return true;
	}
	
	/*
	 */
	bool ControlFlow::load(const char *name, bool merge) {
		Xml xml, parent;
		if(!xml.load(name) || parent.addChild(xml) || !load(parent, merge)) {
			TS_LOGF(Error, "ControlFlow::load(): can't load \"%s\" file\n", name);
			return false;
		}
		return true;
	}
	
	bool ControlFlow::load(const String &name, bool merge) {
		return load(name.get(), merge);
	}
	
	/*
	 */
	void ControlFlow::save(Xml &parent, bool merge) const {
		
		// flow root
		Xml xml(&parent, "flow");
		if(variant) xml.setAttribute("variant", variant);
		if(version) xml.setAttribute("version", version);
		
		// find node dependencies
		Map<uint32_t, uint32_t> type_indices;
		Map<uint32_t, uint32_t> proto_indices;
		Map<uint32_t, uint64_t> proto_inputs;
		Map<uint32_t, uint64_t> proto_outputs;
		if(merge) {
			for(const NodePtr &node : nodes) {
				if(node->index == Maxu32) continue;
				if(protos[node->proto].index == Maxu32) continue;
				auto proto_index_it = proto_indices.find(node->proto);
				if(!proto_index_it) proto_indices.append(node->proto, proto_indices.size());
				const Proto &proto = protos[node->proto];
				for(const NodeInput &input : node->inputs) {
					if(types[input.type].index == Maxu32) continue;
					const ProtoInput &proto_input = proto.inputs[input.index];
					if(!input.connections && input.type == proto_input.type && input.value == proto_input.value) continue;
					if(merge && !input.connections && input.value == proto_input.value) continue;
					if(!proto_input.mask) {
						auto type_index_it = type_indices.find(input.type);
						if(!type_index_it) type_indices.append(input.type, type_indices.size());
						type_index_it = type_indices.find(proto_input.type);
						if(!type_index_it) type_indices.append(proto_input.type, type_indices.size());
					}
					auto it = proto_inputs.find(node->proto);
					if(!it) it = proto_inputs.append(node->proto, 0);
					it->data |= 1ull << input.index;
				}
				for(const NodeOutput &output : node->outputs) {
					if(types[output.type].index == Maxu32) continue;
					const ProtoOutput &proto_output = proto.outputs[output.index];
					if(!output.connections && output.type == proto_output.type && (output.value == proto_output.value || node->is_dynamic)) continue;
					if(merge && !output.connections && (output.value == proto_output.value || node->is_dynamic)) continue;
					if(!proto_output.mask) {
						auto type_index_it = type_indices.find(output.type);
						if(!type_index_it) type_indices.append(output.type, type_indices.size());
						type_index_it = type_indices.find(proto_output.type);
						if(!type_index_it) type_indices.append(proto_output.type, type_indices.size());
					}
					auto it = proto_outputs.find(node->proto);
					if(!it) it = proto_outputs.append(node->proto, 0);
					it->data |= 1ull << output.index;
				}
			}
		}
		
		// save flow
		if(isCreated()) {
			Vector2d position;
			position.x = floor(flow_area.getHorizontalValue() - floor(flow_area.getHorizontalRange() - flow_area.getHorizontalFrame()) * 0.5);
			position.y = floor(flow_area.getVerticalValue() - floor(flow_area.getVerticalRange() - flow_area.getVerticalFrame()) * 0.5);
			Xml parent = Xml(&xml, "controls");
			parent.setData("position", position.v, 2);
			parent.setData("scale", flow_area.getScale());
		}
		
		// save types
		if(type_indices || (types && !merge)) {
			Xml parent = Xml(&xml, "types");
			for(const Type &type : types) {
				if(type.index == Maxu32) continue;
				auto type_index_it = type_indices.find(type.index);
				if(merge && !type_index_it) continue;
				Xml child = Xml(&parent, "type");
				child.setAttribute("name", type.name);
				child.setAttribute("index", (merge) ? type_index_it->data : type.index);
				if(!merge) {
					if(type.text) child.setData("text", type.text);
					if(type.info) child.setData("info", type.info);
					if(type.value) child.setData("value", type.value);
					if(type.input_mask) {
						Array<const char*> masks;
						const TypeMask &mask = type.input_mask;
						for(const Type &type : types) {
							if(!mask.get(type.index)) continue;
							masks.append(type.name.get());
						}
						if(type.input_mask == type.output_mask) child.setData("mask", masks.get(), masks.size());
						else child.setData("input", masks.get(), masks.size());
					}
					if(type.input_mask != type.output_mask) {
						Array<const char*> masks;
						const TypeMask &mask = type.output_mask;
						for(const Type &type : types) {
							if(!mask.get(type.index)) continue;
							masks.append(type.name.get());
						}
						child.setData("output", masks.get(), masks.size());
					}
					if(type.shape != getTypeShape()) child.setData("shape", control_flow_shape_names[type.shape]);
					if(type.color != getTypeColor()) child.setData("color", type.color.c, 4);
					if(type.stroke_style != getTypeStrokeStyle()) save_stroke_style(child, type.stroke_style);
					if(type.gradient_style != getTypeGradientStyle()) save_gradient_style(child, type.gradient_style);
					if(type.edit_mode != ControlEdit::EditModeText) child.setData("edit", type.edit_mode);
					if(type.connection_width != getConnectionWidth() || type.connection_color != getConnectionColor() || type.connection_style != getConnectionStyle()) {
						Xml connection = Xml(&child, "connection");
						if(type.connection_width != getConnectionWidth()) connection.setData("width", type.connection_width);
						if(type.connection_color != getConnectionColor()) connection.setData("color", type.connection_color.c, 4);
						if(type.connection_style != getConnectionStyle()) save_stroke_style(connection, type.connection_style);
					}
				}
			}
			if(!parent.getNumChildren()) xml.removeChild(parent);
		}
		
		// save protos
		if(proto_indices || (protos && !merge)) {
			Xml parent = Xml(&xml, "protos");
			for(const Proto &proto : protos) {
				if(proto.index == Maxu32) continue;
				auto proto_index_it = proto_indices.find(proto.index);
				if(merge && !proto_index_it) continue;
				Xml child = Xml(&parent, "proto");
				child.setAttribute("name", proto.name);
				child.setAttribute("index", (merge) ? proto_index_it->data : proto.index);
				if(!merge) {
					if(proto.text) child.setData("text", proto.text);
					if(proto.title) child.setData("title", proto.title);
					if(proto.value) child.setData("value", proto.value);
					if(proto.state) child.setData("state", proto.state);
					if(proto.info) child.setData("info", proto.info);
					if(proto.color != getProtoColor()) child.setData("color", proto.color.c, 4);
					if(proto.stroke_style != getProtoStrokeStyle()) save_stroke_style(child, proto.stroke_style);
					if(proto.gradient_style != getProtoGradientStyle()) save_gradient_style(child, proto.gradient_style);
				}
				if(proto.inputs) {
					Xml inputs = Xml(&child, "inputs");
					auto input_it = proto_inputs.find(proto.index);
					for(const ProtoInput &input : proto.inputs) {
						if(input.index == Maxu32) continue;
						if(merge && (!input_it || !(input_it->data & (1ull << input.index)))) continue;
						Xml child = Xml(&inputs, "input");
						const Type &type = types[input.type];
						if(!input.mask) child.setAttribute("type", (merge) ? type_indices[input.type] : input.type);
						child.setAttribute("index", input.index);
						if(merge) {
							if(input.name) child.setData("name", input.name);
							else if(input.text && input.text != type.text) child.setData("text", input.text);
						} else {
							if(input.name) child.setData("name", input.name);
							if(input.text && input.text != type.text) child.setData("text", input.text);
							if(input.info && input.info != type.info) child.setData("info", input.info);
							if(input.value && input.value != type.value) child.setData("value", input.value);
							if(input.is_multi) child.setData("multi", input.is_multi);
							if(input.is_final) child.setData("final", input.is_final);
							if(input.is_separator) child.setData("separator", input.is_separator);
						}
					}
					if(!inputs.getNumChildren()) child.removeChild(inputs);
				}
				if(proto.outputs) {
					Xml outputs = Xml(&child, "outputs");
					auto output_it = proto_outputs.find(proto.index);
					for(const ProtoOutput &output : proto.outputs) {
						if(output.index == Maxu32) continue;
						if(merge && (!output_it || !(output_it->data & (1ull << output.index)))) continue;
						Xml child = Xml(&outputs, "output");
						const Type &type = types[output.type];
						if(!output.mask) child.setAttribute("type", (merge) ? type_indices[output.type] : output.type);
						child.setAttribute("index", output.index);
						if(merge) {
							if(output.name) child.setData("name", output.name);
							else if(output.text && output.text != type.text) child.setData("text", output.text);
						} else {
							if(output.name) child.setData("name", output.name);
							if(output.text && output.text != type.text) child.setData("text", output.text);
							if(output.info && output.info != type.info) child.setData("info", output.info);
							if(output.value && output.value != type.value) child.setData("value", output.value);
							if(output.is_multi) child.setData("multi", output.is_multi);
							if(output.is_final) child.setData("final", output.is_final);
							if(output.is_separator) child.setData("separator", output.is_separator);
						}
					}
					if(!outputs.getNumChildren()) child.removeChild(outputs);
				}
			}
			if(!parent.getNumChildren()) xml.removeChild(parent);
		}
		
		// save nodes
		if(nodes) {
			Xml parent = Xml(&xml, "nodes");
			Vector2f center = get_nodes_center();
			for(const NodePtr &node : nodes) {
				if(node->index == Maxu32) continue;
				Xml child = Xml(&parent, "node");
				child.setAttribute("proto", (merge) ? proto_indices[node->proto] : node->proto);
				child.setAttribute("index", node->index);
				if(!merge && node->is_static) child.setData("static", node->is_static);
				if(!merge && node->is_dynamic) child.setData("dynamic", node->is_dynamic);
				if(!node->is_expanded) child.setData("expanded", node->is_expanded);
				Vector2f position = node->position - center;
				if(position != Vector2f::zero) child.setData("position", position.v, 2);
				if(node->value && !node->is_dynamic) child.setData("value", node->value);
				if(node->state) child.setData("state", node->state);
				const Proto &proto = protos[node->proto];
				for(const NodeInput &input : node->inputs) {
					const ProtoInput &proto_input = proto.inputs[input.index];
					if(input.type == proto_input.type && input.value == proto_input.value) continue;
					if(merge && !input.connections && input.value == proto_input.value) continue;
					Xml input_xml = Xml(&child, "input");
					if(input.type != proto_input.type && !proto_input.mask) input_xml.setAttribute("type", (merge) ? type_indices[input.type] : input.type);
					if(input.value != proto_input.value) input_xml.setData("value", input.value);
					input_xml.setAttribute("index", input.index);
				}
				for(const NodeOutput &output : node->outputs) {
					const ProtoOutput &proto_output = proto.outputs[output.index];
					if(output.type == proto_output.type && (output.value == proto_output.value || node->is_dynamic)) continue;
					if(merge && !output.connections && (output.value == proto_output.value || node->is_dynamic)) continue;
					Xml output_xml = Xml(&child, "output");
					if(output.type != proto_output.type && !proto_output.mask) output_xml.setAttribute("type", (merge) ? type_indices[output.type] : output.type);
					if(output.value != proto_output.value && !node->is_dynamic) output_xml.setData("value", output.value);
					output_xml.setAttribute("index", output.index);
				}
				if(node->save_func) node->save_func(this, &child, node->index);
			}
			if(!parent.getNumChildren()) xml.removeChild(parent);
		}
		
		// save connections
		if(nodes) {
			Xml parent = Xml(&xml, "connections");
			for(const NodePtr &node : nodes) {
				if(node->index == Maxu32) continue;
				for(const NodeOutput &output : node->outputs) {
					if(!output.connections) continue;
					Xml child = Xml(&parent, "output");
					child.setAttribute("node", node->index);
					child.setAttribute("index", output.index);
					for(const OutputConnection &connection : output.connections) {
						Xml input = Xml(&child, "input");
						input.setAttribute("node", connection.node);
						input.setAttribute("index", connection.input);
					}
				}
			}
			if(!parent.getNumChildren()) xml.removeChild(parent);
		}
	}
	
	/*
	 */
	bool ControlFlow::save(const char *name, bool merge) const {
		Xml xml;
		save(xml, merge);
		if(!xml.getChild(0u).save(name)) {
			TS_LOGF(Error, "ControlFlow::save(): can't save \"%s\" file\n", name);
			return false;
		}
		return true;
	}
	
	bool ControlFlow::save(const String &name, bool merge) const {
		return save(name.get(), merge);
	}
	
	/*****************************************************************************\
	 *
	 * ControlFlow TypeMask
	 *
	\*****************************************************************************/
	
	/*
	 */
	ControlFlow::TypeMask ControlFlow::TypeMask::operator&(const TypeMask &mask) const {
		TypeMask ret;
		for(uint32_t i = 0; i < NumMasks; i++) {
			ret.masks[i] = masks[i] & mask.masks[i];
		}
		return ret;
	}
	
	ControlFlow::TypeMask ControlFlow::TypeMask::operator|(const TypeMask &mask) const {
		TypeMask ret;
		for(uint32_t i = 0; i < NumMasks; i++) {
			ret.masks[i] = masks[i] | mask.masks[i];
		}
		return ret;
	}
	
	ControlFlow::TypeMask ControlFlow::TypeMask::operator~() const {
		TypeMask ret;
		for(uint32_t i = 0; i < NumMasks; i++) {
			ret.masks[i] = ~masks[i];
		}
		return ret;
	}
	
	/*
	 */
	bool ControlFlow::TypeMask::operator==(const TypeMask &mask) const {
		for(uint32_t i = 0; i < NumMasks; i++) {
			if(masks[i] != mask.masks[i]) return false;
		}
		return true;
	}
	
	bool ControlFlow::TypeMask::operator!=(const TypeMask &mask) const {
		for(uint32_t i = 0; i < NumMasks; i++) {
			if(masks[i] != mask.masks[i]) return true;
		}
		return false;
	}
	
	ControlFlow::TypeMask::operator bool() const {
		for(uint32_t i = 0; i < NumMasks; i++) {
			if(masks[i] != 0) return true;
		}
		return false;
	}
	
	/*
	 */
	void ControlFlow::TypeMask::set(uint32_t type, bool value) {
		TS_ASSERT(type < NumTypes && "ControlFlow::TypeMask::set(): invalid type");
		if(value) masks[type / NumBits] |= (1ull << (uint64_t)(type % NumBits));
		else masks[type / NumBits] &= ~(1ull << (uint64_t)(type % NumBits));
	}
	
	bool ControlFlow::TypeMask::get(uint32_t type) const {
		TS_ASSERT(type < NumTypes && "ControlFlow::TypeMask::get(): invalid type");
		return ((masks[type / NumBits] & (1ull << (uint64_t)(type % NumBits))) != 0);
	}
	
	/*****************************************************************************\
	 *
	 * ControlFlow Types
	 *
	\*****************************************************************************/
	
	/*
	 */
	void ControlFlow::clearTypes() {
		types.clear();
		type_names.clear();
	}
	
	void ControlFlow::reserveTypes(uint32_t num_types) {
		types.reserve(num_types);
	}
	
	/*
	 */
	uint32_t ControlFlow::addType(const char *name, const Color &color, Shape shape, const TypeMask &mask) {
		Type type;
		type.name = name;
		type.index = types.size();
		type.input_mask = mask;
		type.output_mask = mask;
		type.shape = shape;
		type.color = color;
		type.stroke_style = getTypeStrokeStyle();
		type.gradient_style = getTypeGradientStyle();
		type.edit_mode = ControlEdit::EditModeText;
		type.connection_color = color;
		type.connection_width = getConnectionWidth();
		type.connection_style = getConnectionStyle();
		type_names.append(type.name, type.index);
		types.append(type);
		return type.index;
	}
	
	uint32_t ControlFlow::addType(const String &name, const Color &color, Shape shape, const TypeMask &mask) {
		return addType(name.get(), color, shape, mask);
	}
	
	/*
	 */
	uint32_t ControlFlow::findType(const char *name) const {
		auto it = type_names.find(name);
		if(it) return it->data;
		return Maxu32;
	}
	
	uint32_t ControlFlow::findType(const String &name) const {
		return findType(name.get());
	}
	
	/*
	 */
	void ControlFlow::removeType(uint32_t index) {
		Type &type = types[index];
		auto it = type_names.find(type.name);
		if(it) type_names.remove(it);
		type.name.clear();
		type.index = Maxu32;
	}
	
	/*
	 */
	void ControlFlow::setTypeName(uint32_t index, const char *name) {
		Type &type = types[index];
		auto it = type_names.find(type.name);
		if(it) type_names.remove(it);
		type.name = name;
		type_names.append(type.name, type.index);
	}
	
	void ControlFlow::setTypeName(uint32_t index, const String &name) {
		setTypeName(index, name.get());
	}
	
	/*****************************************************************************\
	 *
	 * ControlFlow Protos
	 *
	\*****************************************************************************/
	
	/*
	 */
	void ControlFlow::clearProtos() {
		protos.clear();
		proto_names.clear();
	}
	
	void ControlFlow::reserveProtos(uint32_t num_protos) {
		protos.reserve(num_protos);
	}
	
	/*
	 */
	uint32_t ControlFlow::addProto(const char *name, const char *text) {
		uint32_t index = addProto(name);
		setProtoText(index, text);
		return index;
	}
	
	uint32_t ControlFlow::addProto(const String &name, const String &text) {
		return addProto(name.get(), text.get());
	}
	
	/*
	 */
	uint32_t ControlFlow::addProto(const char *name, uint32_t input_type, uint32_t output_type) {
		Proto proto;
		proto.name = name;
		proto.text = name;
		proto.index = protos.size();
		proto.color = getProtoColor();
		proto.stroke_style = getProtoStrokeStyle();
		proto.gradient_style = getProtoGradientStyle();
		if(input_type != Maxu32) {
			ProtoInput input;
			input.type = input_type;
			input.index = proto.inputs.size();
			input.text = getTypeText(input_type);
			input.info = types[input_type].info;
			proto.inputs.append(input);
		}
		if(output_type != Maxu32) {
			ProtoOutput output;
			output.type = output_type;
			output.index = proto.outputs.size();
			output.text = getTypeText(output_type);
			output.info = types[output_type].info;
			proto.outputs.append(output);
		}
		proto_names.append(proto.name, proto.index);
		update_proto_tree = true;
		protos.append(proto);
		return proto.index;
	}
	
	uint32_t ControlFlow::addProto(const String &name, uint32_t input, uint32_t output) {
		return addProto(name.get(), input, output);
	}
	
	/*
	 */
	uint32_t ControlFlow::addProto(const char *name, const InitializerList<uint32_t> &inputs, const InitializerList<uint32_t> &outputs) {
		Proto proto;
		proto.name = name;
		proto.text = name;
		proto.index = protos.size();
		proto.color = getProtoColor();
		proto.stroke_style = getProtoStrokeStyle();
		proto.gradient_style = getProtoGradientStyle();
		for(uint32_t input_type : inputs) {
			ProtoInput input;
			input.type = input_type;
			input.index = proto.inputs.size();
			input.text = getTypeText(input_type);
			input.info = types[input_type].info;
			proto.inputs.append(input);
		}
		for(uint32_t output_type : outputs) {
			ProtoOutput output;
			output.type = output_type;
			output.index = proto.outputs.size();
			output.text = getTypeText(output_type);
			output.info = types[output_type].info;
			proto.outputs.append(output);
		}
		proto_names.append(proto.name, proto.index);
		update_proto_tree = true;
		protos.append(proto);
		return proto.index;
	}
	
	uint32_t ControlFlow::addProto(const String &name, const InitializerList<uint32_t> &inputs, const InitializerList<uint32_t> &outputs) {
		return addProto(name.get(), inputs, outputs);
	}
	
	/*
	 */
	uint32_t ControlFlow::findProto(const char *name) const {
		auto it = proto_names.find(name);
		if(it) return it->data;
		for(const Proto &proto : protos) {
			if(proto.text == name) return proto.index;
		}
		return Maxu32;
	}
	
	uint32_t ControlFlow::findProto(const String &name) const {
		return findProto(name.get());
	}
	
	/*
	 */
	void ControlFlow::removeProto(uint32_t index) {
		Proto &proto = protos[index];
		auto it = proto_names.find(proto.name);
		if(it) proto_names.remove(it);
		proto.name.clear();
		proto.index = Maxu32;
		update_proto_tree = true;
	}
	
	/*
	 */
	void ControlFlow::setProtoName(uint32_t index, const char *name) {
		Proto &proto = protos[index];
		auto it = proto_names.find(proto.name);
		if(it) proto_names.remove(it);
		proto.name = name;
		proto_names.append(proto.name, proto.index);
	}
	
	void ControlFlow::setProtoName(uint32_t index, const String &name) {
		setProtoName(index, name.get());
	}
	
	/*
	 */
	void ControlFlow::clearProtoInputs(uint32_t proto) {
		protos[proto].inputs.clear();
	}
	
	void ControlFlow::reserveProtoInputs(uint32_t proto, uint32_t num_inputs) {
		protos[proto].inputs.reserve(num_inputs);
	}
	
	/*
	 */
	uint32_t ControlFlow::addProtoInput(uint32_t proto, const char *name, uint32_t type, bool is_multi) {
		ProtoInput input;
		input.name = name;
		input.type = type;
		input.is_multi = is_multi;
		input.info = types[type].info;
		input.value = types[type].value;
		input.index = protos[proto].inputs.size();
		protos[proto].inputs.append(input);
		return input.index;
	}
	
	uint32_t ControlFlow::addProtoInput(uint32_t proto, const String &name, uint32_t type, bool is_multi) {
		return addProtoInput(proto, name.get(), type, is_multi);
	}
	
	/*
	 */
	uint32_t ControlFlow::addProtoInput(uint32_t proto, const char *name, const char *text, uint32_t type, bool is_multi) {
		uint32_t index = addProtoInput(proto, name, type, is_multi);
		setProtoInputText(proto, index, text);
		return index;
	}
	
	uint32_t ControlFlow::addProtoInput(uint32_t proto, const String &name, const String &text, uint32_t type, bool is_multi) {
		return addProtoInput(proto, name.get(), text.get(), type, is_multi);
	}
	
	/*
	 */
	uint32_t ControlFlow::addProtoInput(uint32_t proto, const char *name, const char *text, const char *value, uint32_t type, bool is_multi) {
		uint32_t index = addProtoInput(proto, name, type, is_multi);
		setProtoInputText(proto, index, text);
		setProtoInputValue(proto, index, value);
		return index;
	}
	
	uint32_t ControlFlow::addProtoInput(uint32_t proto, const String &name, const String &text, const String &value, uint32_t type, bool is_multi) {
		return addProtoInput(proto, name.get(), text.get(), value.get(), type, is_multi);
	}
	
	/*
	 */
	uint32_t ControlFlow::findProtoInput(uint32_t proto, const char *name) const {
		const auto &inputs = protos[proto].inputs;
		for(const ProtoInput &input : inputs) {
			if(input.name == name) return input.index;
		}
		for(const ProtoInput &input : inputs) {
			if(input.text == name) return input.index;
		}
		for(const ProtoInput &input : inputs) {
			if(types[input.type].name == name) return input.index;
		}
		for(const ProtoInput &input : inputs) {
			if(types[input.type].text == name) return input.index;
		}
		return Maxu32;
	}
	
	uint32_t ControlFlow::findProtoInput(uint32_t proto, const String &name) const {
		return findProtoInput(proto, name.get());
	}
	
	/*
	 */
	Array<uint32_t> ControlFlow::findProtoInputs(uint32_t proto, const char *name) const {
		Array<uint32_t> ret;
		for(const ProtoInput &input : protos[proto].inputs) {
			if(input.name == name || input.text == name || types[input.type].name == name || types[input.type].text == name) ret.append(input.index);
		}
		return move(ret);
	}
	
	Array<uint32_t> ControlFlow::findProtoInputs(uint32_t proto, const String &name) const {
		return move(findProtoInputs(proto, name.get()));
	}
	
	/*
	 */
	void ControlFlow::removeProtoInput(uint32_t proto, uint32_t index) {
		ProtoInput &input = protos[proto].inputs[index];
		input.name.clear();
		input.index = Maxu32;
	}
	
	/*
	 */
	bool ControlFlow::setProtoInputInfo(uint32_t proto, const char *name, const char *info) {
		uint32_t index = findProtoInput(proto, name);
		if(index == Maxu32) {
			TS_LOGF(Error, "ControlFlow::setProtoInputInfo(): can't find \"%s\" input\n", name);
			return false;
		}
		setProtoInputInfo(proto, index, info);
		return true;
	}
	
	/*
	 */
	bool ControlFlow::setProtoInputValue(uint32_t proto, const char *name, const char *value) {
		uint32_t index = findProtoInput(proto, name);
		if(index == Maxu32) {
			TS_LOGF(Error, "ControlFlow::setProtoInputValue(): can't find \"%s\" input\n", name);
			return false;
		}
		setProtoInputValue(proto, index, value);
		return true;
	}
	
	bool ControlFlow::setProtoInputValue(uint32_t proto, const char *name, const String &value) {
		return setProtoInputValue(proto, name, value.get());
	}
	
	bool ControlFlow::setProtoInputValue(uint32_t proto, const String &name, const String &value) {
		return setProtoInputValue(proto, name.get(), value.get());
	}
	
	const String &ControlFlow::getProtoInputValue(uint32_t proto, const char *name) const {
		uint32_t index = findProtoInput(proto, name);
		if(index == Maxu32) {
			TS_LOGF(Error, "ControlFlow::getProtoInputValue(): can't find \"%s\" input\n", name);
			return String::null;
		}
		return getProtoInputValue(proto, index);
	}
	
	const String &ControlFlow::getProtoInputValue(uint32_t proto, const String &name) const {
		return getProtoInputValue(proto, name.get());
	}
	
	/*
	 */
	bool ControlFlow::setProtoInputType(uint32_t proto, const char *name, uint32_t type) {
		uint32_t index = findProtoInput(proto, name);
		if(index == Maxu32) {
			TS_LOGF(Error, "ControlFlow::setProtoInputType(): can't find \"%s\" input\n", name);
			return false;
		}
		setProtoInputType(proto, index, type);
		return true;
	}
	
	/*
	 */
	bool ControlFlow::setProtoMultiInput(uint32_t proto, const char *name, bool is_multi) {
		uint32_t index = findProtoInput(proto, name);
		if(index == Maxu32) {
			TS_LOGF(Error, "ControlFlow::setProtoMultiInput(): can't find \"%s\" input\n", name);
			return false;
		}
		setProtoMultiInput(proto, index, is_multi);
		return true;
	}
	
	/*
	 */
	bool ControlFlow::setProtoFinalInput(uint32_t proto, const char *name, bool is_final) {
		uint32_t index = findProtoInput(proto, name);
		if(index == Maxu32) {
			TS_LOGF(Error, "ControlFlow::setProtoFinalInput(): can't find \"%s\" input\n", name);
			return false;
		}
		setProtoFinalInput(proto, index, is_final);
		return true;
	}
	
	/*
	 */
	bool ControlFlow::setProtoSeparatorInput(uint32_t proto, const char *name, bool is_separator) {
		uint32_t index = findProtoInput(proto, name);
		if(index == Maxu32) {
			TS_LOGF(Error, "ControlFlow::setProtoSeparatorInput(): can't find \"%s\" input\n", name);
			return false;
		}
		setProtoSeparatorInput(proto, index, is_separator);
		return true;
	}
	
	/*
	 */
	void ControlFlow::clearProtoOutputs(uint32_t proto) {
		protos[proto].outputs.clear();
	}
	
	void ControlFlow::reserveProtoOutputs(uint32_t proto, uint32_t num_outputs) {
		protos[proto].outputs.reserve(num_outputs);
	}
	
	/*
	 */
	uint32_t ControlFlow::addProtoOutput(uint32_t proto, const char *name, uint32_t type, bool is_multi) {
		ProtoOutput output;
		output.name = name;
		output.type = type;
		output.is_multi = is_multi;
		output.info = types[type].info;
		output.value = types[type].value;
		output.index = protos[proto].outputs.size();
		protos[proto].outputs.append(output);
		return output.index;
	}
	
	uint32_t ControlFlow::addProtoOutput(uint32_t proto, const String &name, uint32_t type, bool is_multi) {
		return addProtoOutput(proto, name.get(), type, is_multi);
	}
	
	/*
	 */
	uint32_t ControlFlow::addProtoOutput(uint32_t proto, const char *name, const char *text, uint32_t type, bool is_multi) {
		uint32_t index = addProtoOutput(proto, name, type, is_multi);
		setProtoOutputText(proto, index, text);
		return index;
	}
	
	uint32_t ControlFlow::addProtoOutput(uint32_t proto, const String &name, const String &text, uint32_t type, bool is_multi) {
		return addProtoOutput(proto, name.get(), text.get(), type, is_multi);
	}
	
	/*
	 */
	uint32_t ControlFlow::addProtoOutput(uint32_t proto, const char *name, const char *text, const char *value, uint32_t type, bool is_multi) {
		uint32_t index = addProtoOutput(proto, name, type, is_multi);
		setProtoOutputText(proto, index, text);
		setProtoOutputValue(proto, index, value);
		return index;
	}
	
	uint32_t ControlFlow::addProtoOutput(uint32_t proto, const String &name, const String &text, const String &value, uint32_t type, bool is_multi) {
		return addProtoOutput(proto, name.get(), text.get(), value.get(), type, is_multi);
	}
	
	/*
	 */
	uint32_t ControlFlow::findProtoOutput(uint32_t proto, const char *name) const {
		const auto &outputs = protos[proto].outputs;
		for(const ProtoOutput &output : outputs) {
			if(output.name == name) return output.index;
		}
		for(const ProtoOutput &output : outputs) {
			if(output.text == name) return output.index;
		}
		for(const ProtoOutput &output : outputs) {
			if(types[output.type].name == name) return output.index;
		}
		for(const ProtoOutput &output : outputs) {
			if(types[output.type].text == name) return output.index;
		}
		return Maxu32;
	}
	
	uint32_t ControlFlow::findProtoOutput(uint32_t proto, const String &name) const {
		return findProtoOutput(proto, name.get());
	}
	
	/*
	 */
	Array<uint32_t> ControlFlow::findProtoOutputs(uint32_t proto, const char *name) const {
		Array<uint32_t> ret;
		for(const ProtoOutput &output : protos[proto].outputs) {
			if(output.name == name || output.text == name || types[output.type].name == name || types[output.type].text == name) ret.append(output.index);
		}
		return move(ret);
	}
	
	Array<uint32_t> ControlFlow::findProtoOutputs(uint32_t proto, const String &name) const {
		return move(findProtoOutputs(proto, name.get()));
	}
	
	/*
	 */
	void ControlFlow::removeProtoOutput(uint32_t proto, uint32_t index) {
		ProtoOutput &output = protos[proto].outputs[index];
		output.name.clear();
		output.index = Maxu32;
	}
	
	/*
	 */
	bool ControlFlow::setProtoOutputInfo(uint32_t proto, const char *name, const char *info) {
		uint32_t index = findProtoOutput(proto, name);
		if(index == Maxu32) {
			TS_LOGF(Error, "ControlFlow::setProtoOutputInfo(): can't find \"%s\" input\n", name);
			return false;
		}
		setProtoOutputInfo(proto, index, info);
		return true;
	}
	
	/*
	 */
	bool ControlFlow::setProtoOutputValue(uint32_t proto, const char *name, const char *value) {
		uint32_t index = findProtoOutput(proto, name);
		if(index == Maxu32) {
			TS_LOGF(Error, "ControlFlow::setProtoOutputValue(): can't find \"%s\" input\n", name);
			return false;
		}
		setProtoOutputValue(proto, index, value);
		return true;
	}
	
	bool ControlFlow::setProtoOutputValue(uint32_t proto, const char *name, const String &value) {
		return setProtoOutputValue(proto, name, value.get());
	}
	
	bool ControlFlow::setProtoOutputValue(uint32_t proto, const String &name, const String &value) {
		return setProtoOutputValue(proto, name.get(), value.get());
	}
	
	const String &ControlFlow::getProtoOutputValue(uint32_t proto, const char *name) const {
		uint32_t index = findProtoOutput(proto, name);
		if(index == Maxu32) {
			TS_LOGF(Error, "ControlFlow::getProtoOutputValue(): can't find \"%s\" input\n", name);
			return String::null;
		}
		return getProtoOutputValue(proto, index);
	}
	
	const String &ControlFlow::getProtoOutputValue(uint32_t proto, const String &name) const {
		return getProtoOutputValue(proto, name.get());
	}
	
	/*
	 */
	bool ControlFlow::setProtoOutputType(uint32_t proto, const char *name, uint32_t type) {
		uint32_t index = findProtoOutput(proto, name);
		if(index == Maxu32) {
			TS_LOGF(Error, "ControlFlow::setProtoOutputType(): can't find \"%s\" input\n", name);
			return false;
		}
		setProtoOutputType(proto, index, type);
		return true;
	}
	
	/*
	 */
	bool ControlFlow::setProtoMultiOutput(uint32_t proto, const char *name, bool is_multi) {
		uint32_t index = findProtoOutput(proto, name);
		if(index == Maxu32) {
			TS_LOGF(Error, "ControlFlow::setProtoMultiOutput(): can't find \"%s\" input\n", name);
			return false;
		}
		setProtoMultiOutput(proto, index, is_multi);
		return true;
	}
	
	/*
	 */
	bool ControlFlow::setProtoFinalOutput(uint32_t proto, const char *name, bool is_final) {
		uint32_t index = findProtoOutput(proto, name);
		if(index == Maxu32) {
			TS_LOGF(Error, "ControlFlow::setProtoFinalOutput(): can't find \"%s\" input\n", name);
			return false;
		}
		setProtoFinalOutput(proto, index, is_final);
		return true;
	}
	
	/*
	 */
	bool ControlFlow::setProtoSeparatorOutput(uint32_t proto, const char *name, bool is_separator) {
		uint32_t index = findProtoOutput(proto, name);
		if(index == Maxu32) {
			TS_LOGF(Error, "ControlFlow::setProtoSeparatorOutput(): can't find \"%s\" input\n", name);
			return false;
		}
		setProtoSeparatorOutput(proto, index, is_separator);
		return true;
	}
	
	/*****************************************************************************\
	 *
	 * ControlFlow Nodes
	 *
	\*****************************************************************************/
	
	/*
	 */
	void ControlFlow::clearNodes() {
		
		is_clear = true;
		
		if(isCreated()) {
			flow_panel.setSize(4096.0f, 2048.0f);
		}
		
		for(const NodePtr &node : nodes) {
			if(node->index == Maxu32) continue;
			removeNode(node->index);
		}
		nodes.clear();
		
		current_node_index = Maxu32;
		current_input_index = Maxu32;
		current_output_index = Maxu32;
		
		input_node_index = Maxu32;
		
		selected_nodes.clear();
		prev_selected_nodes.clear();
		
		update_nodes.clear();
		prev_update_nodes.clear();
		next_update_nodes.clear();
		
		spatial_indices.clear();
		spatial_nodes.clear();
		
		for(auto &action : undo_actions) {
			for(Node &node : action->nodes) {
				remove_node(node);
			}
		}
		for(auto &action : redo_actions) {
			for(Node &node : action->nodes) {
				remove_node(node);
			}
		}
		undo_actions.release();
		redo_actions.release();
		
		is_updated = false;
		
		is_clear = false;
	}
	
	void ControlFlow::reserveNodes(uint32_t num_nodes) {
		nodes.reserve(num_nodes);
	}
	
	/*
	 */
	uint32_t ControlFlow::addNode(uint32_t proto_index, const Vector2f &position, const char *value, const char *state) {
		
		// node proto
		const Proto &proto = protos[proto_index];
		
		// create node
		Node *node = new Node();
		node->value = value;
		node->state = state;
		node->proto = proto_index;
		node->index = nodes.size();
		node->position = position;
		
		// create dialog
		if(isCreated()) {
			
			// create node dialog
			node->dialog = ControlDialog(&flow_grid);
			node->dialog.setPosition(Vector3f(position, 0.0f));
			node->dialog.setAlign(AlignCenter | AlignOverlap);
			node->dialog.setResizable(false);
			node->dialog.setConstrained(false);
			node->dialog.setColor(proto.color * (1.0f / 0.9f));
			node->dialog.setStateColor(StateNormal, Color(0.9f));
			node->dialog.setStateColor(StateFocused, Color(1.0f));
			node->dialog.setStateColor(StatePressed, Color(1.0f));
			node->dialog.setStrokeStyle(proto.stroke_style);
			node->dialog.setGradientStyle(proto.gradient_style);
			if(proto.gradient_style) node->dialog.setMode(CanvasElement::ModeGradient);
			node->dialog.setUpdatedCallback(makeFunction(node_updated_callback, ControlDialog::null, this, node->index));
			node->dialog.setPressedCallback(makeFunction(node_pressed_callback, ControlRect::null, 0.0f, 0.0f, this, node->index));
			node->dialog.setReleasedCallback(makeFunction(node_released_callback, ControlRect::null, 0.0f, 0.0f, this, node->index));
			node->dialog.setClicked2Callback(makeFunction(node_clicked2_callback, ControlRect::null, this, node->index));
			if(proto.info) tooltip->addTooltip(node->dialog, proto.info);
			
			// create node text
			node->title_text = ControlText(&node->dialog, proto.text);
			node->title_text.setMargin(spacing.x, spacing.x, spacing.y, 0.0f);
			node->title_text.setAlign(AlignTop | AlignCenterX);
			node->title_text.setFontName("sansb.ttf");
			
			// create main grid
			node->main_grid = ControlGrid(&node->dialog, 3);
			node->main_grid.setAlign(AlignExpand);
			
			// create input grid
			node->input_grid = ControlGrid(&node->main_grid, 2, spacing.x, spacing.y);
			node->input_grid.setMargin(Rect(0.0f, spacing.x, 0.0f, 0.0f));
			node->input_grid.setAlign(AlignLeftTop);
			
			// create node grid
			node->node_grid = ControlGrid(&node->main_grid);
			node->node_grid.setAlign(AlignTop);
			
			// create output grid
			node->output_grid = ControlGrid(&node->main_grid, 2, spacing.x, spacing.y);
			node->output_grid.setMargin(Rect(spacing.x, 0.0f, 0.0f, 0.0f));
			node->output_grid.setAlign(AlignRightBottom);
		}
		
		// create inputs
		node->inputs.reserve(proto.inputs.size());
		for(const ProtoInput &proto_input : proto.inputs) {
			NodeInput node_input;
			node_input.value = proto_input.value;
			node_input.type = proto_input.type;
			node_input.index = node->inputs.size();
			
			// create socket
			if(isCreated()) {
				
				// input separator
				if(proto_input.is_separator) {
					uint32_t index = node->input_grid.getNumChildren();
					node->input_grid.setRowSpacing(index / 2, spacing.y * 2.0f);
				}
				
				// input socket
				node_input.socket = makeAutoPtr(create_socket(&node->input_grid, types[proto_input.type]));
				node_input.socket->setAlign(AlignLeft | AlignCenterY);
				node_input.socket->setPressedCallback(makeFunction(input_pressed_callback, nullptr, 0.0f, 0.0f, this, node->index, node_input.index));
				node_input.socket->setReleasedCallback(makeFunction(input_released_callback, nullptr, 0.0f, 0.0f, this, node->index, node_input.index));
				node_input.socket->setClicked2Callback(makeFunction(input_clicked2_callback, nullptr, this, node->index, node_input.index));
				if(proto_input.info) tooltip->addTooltip(node_input.socket.ref(), proto_input.info);
				else tooltip->addTooltip(node_input.socket.ref(), types[proto_input.type].name);
				
				// input text
				node_input.text = ControlText(&node->input_grid, proto_input.text);
				node_input.text.setAlign(AlignLeft | AlignCenterY);
			}
			
			// add input
			node->inputs.append(node_input);
		}
		
		// create outputs
		node->outputs.reserve(proto.outputs.size());
		for(const ProtoOutput &proto_output : proto.outputs) {
			NodeOutput node_output;
			node_output.value = proto_output.value;
			node_output.type = proto_output.type;
			node_output.index = node->outputs.size();
			
			// create socket
			if(isCreated()) {
				
				// input separator
				if(proto_output.is_separator) {
					uint32_t index = node->output_grid.getNumChildren();
					node->output_grid.setRowSpacing(index / 2, spacing.y * 2.0f);
				}
				
				// output text
				node_output.text = ControlText(&node->output_grid, proto_output.text);
				node_output.text.setAlign(AlignRight | AlignCenterY);
				
				// output socket
				node_output.socket = makeAutoPtr(create_socket(&node->output_grid, types[proto_output.type]));
				node_output.socket->setAlign(AlignRight | AlignCenterY);
				node_output.socket->setPressedCallback(makeFunction(output_pressed_callback, nullptr, 0.0f, 0.0f, this, node->index, node_output.index));
				node_output.socket->setReleasedCallback(makeFunction(output_released_callback, nullptr, 0.0f, 0.0f, this, node->index, node_output.index));
				node_output.socket->setClicked2Callback(makeFunction(output_clicked2_callback, nullptr, this, node->index, node_output.index));
				if(proto_output.info) tooltip->addTooltip(node_output.socket.ref(), proto_output.info);
				else tooltip->addTooltip(node_output.socket.ref(), types[proto_output.type].name);
			}
			
			// add output
			node->outputs.append(node_output);
		}
		
		// update node
		update_nodes.append(node->index);
		
		// add node
		nodes.append(makeAutoPtr(node));
		
		// input create callbacks
		for(const ProtoInput &proto_input : proto.inputs) {
			const Type &type = types[proto_input.type];
			if(type.create_func) type.create_func(this, node->inputs[proto_input.index].socket.get(), type.index);
			if(proto_input.create_func) proto_input.create_func(this, node->input_grid, node->index, proto_input.index);
		}
		
		// output create callbacks
		for(const ProtoOutput &proto_output : proto.outputs) {
			const Type &type = types[proto_output.type];
			if(type.create_func) type.create_func(this, node->inputs[proto_output.index].socket.get(), type.index);
			if(proto_output.create_func) proto_output.create_func(this, node->output_grid, node->index, proto_output.index);
		}
		
		// proto create callback
		if(proto.create_func) proto.create_func(this, node->node_grid, node->index);
		
		return node->index;
	}
	
	uint32_t ControlFlow::addNode(uint32_t proto_index, const Vector2f &position, const String &value, const String &state) {
		return addNode(proto_index, position, value.get(), state.get());
	}
	
	/*
	 */
	uint32_t ControlFlow::findNode(const char *name) const {
		for(const NodePtr &node : nodes) {
			if(node->index == Maxu32) continue;
			if(protos[node->proto].name == name) return node->index;
		}
		for(const NodePtr &node : nodes) {
			if(node->index == Maxu32) continue;
			if(protos[node->proto].text == name) return node->index;
		}
		return Maxu32;
	}
	
	uint32_t ControlFlow::findNode(const String &name) const {
		return findNode(name.get());
	}
	
	/*
	 */
	Array<uint32_t> ControlFlow::findNodes(const char *name) const {
		Array<uint32_t> ret;
		for(const NodePtr &node : nodes) {
			if(node->index == Maxu32) continue;
			const Proto &proto = protos[node->proto];
			if(proto.name == name || proto.text == name) ret.append(node->index);
		}
		return move(ret);
	}
	
	Array<uint32_t> ControlFlow::findNodes(const String &name) const {
		return move(findNodes(name.get()));
	}
	
	/*
	 */
	void ControlFlow::removeNode(uint32_t node_index) {
		
		// clear node
		NodePtr &node = nodes[node_index];
		if(node->index == Maxu32) return;
		if(node->remove_func) node->remove_func(this, node_index);
		const Proto &proto = protos[node->proto];
		if(proto.remove_func) proto.remove_func(this, node_index);
		clearConnections(node_index);
		node->index = Maxu32;
		
		// remove node
		remove_node(node.ref());
		
		// change mode
		mode = ModeClear;
	}
	
	void ControlFlow::remove_node(Node &node) {
		
		// remove socket elements
		for(NodeInput &input : node.inputs) {
			if(input.socket) removed_elements.append(input.socket.release());
		}
		for(NodeOutput &output : node.outputs) {
			if(output.socket) removed_elements.append(output.socket.release());
		}
		
		// release node
		if(node.dialog) {
			flow_grid.removeChild(node.dialog);
			removed_controls.append(node.dialog);
			node.dialog.clearPtr();
		}
	}
	
	/*
	 */
	void ControlFlow::setNodeValue(uint32_t index, const char *value, bool action) {
		NodePtr &node = nodes[index];
		if(node->value != value || action) {
			if(action) {
				Action *action = new Action(ActionValue);
				action->indices.append(index);
				action->data = node->value;
				add_action(action);
			}
			node->value = value;
		}
	}
	
	void ControlFlow::setNodeValue(uint32_t index, const String &value, bool action) {
		setNodeValue(index, value.get(), action);
	}
	
	/*
	 */
	void ControlFlow::setNodeState(uint32_t index, const char *state, bool action) {
		NodePtr &node = nodes[index];
		if(node->state != state || action) {
			if(action) {
				Action *action = new Action(ActionState);
				action->indices.append(index);
				action->data = node->state;
				add_action(action);
			}
			node->state = state;
		}
	}
	
	void ControlFlow::setNodeState(uint32_t index, const String &state, bool action) {
		setNodeState(index, state.get(), action);
	}
	
	/*
	 */
	void ControlFlow::setNodePosition(uint32_t node_index, const Vector2f &position) {
		NodePtr &node = nodes[node_index];
		if(node->index == Maxu32) return;
		Vector2f offset = position - node->position;
		if(isCreated()) {
			node->dialog.setPosition(Vector3f(position, 0.0f));
			for(NodeInput &input : node->inputs) {
				input.socket->setOffset(input.socket->getOffset() + Vector3f(offset, 0.0f));
			}
			for(NodeOutput &output : node->outputs) {
				output.socket->setOffset(output.socket->getOffset() + Vector3f(offset, 0.0f));
			}
		}
		update_nodes.append(node_index);
		node->position = position;
	}
	
	/*
	 */
	void ControlFlow::updateNode(uint32_t node_index, bool inverse) {
		const NodePtr &node = nodes[node_index];
		const Proto &proto = protos[node->proto];
		if(proto.update_func) proto.update_func(this, node->index, inverse);
		if(node->update_func) node->update_func(this, node->index, inverse);
	}
	
	/*
	 */
	void ControlFlow::cloneNodes(Array<uint32_t> &node_indices) {
		
		// create nodes
		Array<uint32_t> old_node_indices = node_indices;
		for(uint32_t i = 0; i < node_indices.size(); i++) {
			uint32_t index = node_indices[i];
			const Node *node = nodes[index].get();
			if(node->is_static) continue;
			if(node->index == Maxu32) continue;
			node_indices[i] = addNode(node->proto, node->position, getNodeValue(index), getNodeState(index));
			for(const NodeInput &input : node->inputs) {
				setInputValue(node_indices[i], input.index, getInputValue(index, input.index));
			}
			for(const NodeOutput &output : node->outputs) {
				setOutputValue(node_indices[i], output.index, getOutputValue(index, output.index));
			}
			if(nodes[node_indices[i]]->create_func) {
				nodes[node_indices[i]]->create_func(this, node_indices[i]);
			}
		}
		
		// create connections
		for(uint32_t i = 0; i < old_node_indices.size(); i++) {
			uint32_t index = old_node_indices[i];
			const NodePtr &node = nodes[index];
			if(node->is_static) continue;
			if(node->index == Maxu32) continue;
			for(const NodeInput &input : node->inputs) {
				for(const InputConnection &connection : input.connections) {
					uint32_t index = old_node_indices.findIndex(connection.node);
					if(index != Maxu32) addInputConnection(node_indices[i], input.index, node_indices[index], connection.output);
				}
			}
			for(const NodeOutput &output : node->outputs) {
				for(const OutputConnection &connection : output.connections) {
					uint32_t index = old_node_indices.findIndex(connection.node);
					if(index != Maxu32) addOutputConnection(node_indices[i], output.index, node_indices[index], connection.input);
				}
			}
		}
	}
	
	/*
	 */
	void ControlFlow::setInputType(uint32_t node_index, uint32_t index, uint32_t type, bool force) {
		NodePtr &node = nodes[node_index];
		NodeInput &input = node->inputs[index];
		if(input.type != type || force) {
			input.type = type;
			Canvas canvas = getCanvas();
			const Type &input_type = types[input.type];
			canvas.removeElement(input.socket->getElement());
			input.socket->setElement(create_socket(canvas, input_type));
			input.socket->setColor(input.socket->getElement().getColor());
			for(const InputConnection &connection : input.connections) {
				const ProtoOutput &proto_output = protos[getNodeProto(connection.node)].outputs[connection.output];
				if(proto_output.attach_func) proto_output.attach_func(this, connection.node, connection.output, node_index, index);
			}
		}
	}
	
	/*
	 */
	bool ControlFlow::setInputType(uint32_t node, const char *name, uint32_t type, bool force) {
		uint32_t index = findInput(node, name);
		if(index == Maxu32) {
			TS_LOGF(Error, "ControlFlow::setInputType(): can't find \"%s\" input\n", name);
			return false;
		}
		setInputType(node, index, type, force);
		return true;
	}
	
	bool ControlFlow::setInputType(uint32_t node, const String &name, uint32_t type, bool force) {
		return setInputType(node, name.get(), type, force);
	}
	
	uint32_t ControlFlow::getInputType(uint32_t node, const char *name) const {
		uint32_t index = findInput(node, name);
		if(index == Maxu32) {
			TS_LOGF(Error, "ControlFlow::getInputType(): can't find \"%s\" input\n", name);
			return Maxu32;
		}
		return getInputType(node, index);
	}
	
	uint32_t ControlFlow::getInputType(uint32_t node, const String &name) const {
		return getInputType(node, name.get());
	}
	
	/*
	 */
	void ControlFlow::setInputValue(uint32_t node_index, uint32_t index, const char *value, bool action) {
		NodePtr &node = nodes[node_index];
		NodeInput &input = node->inputs[index];
		if(input.value != value || action) {
			if(action) {
				Action *action = new Action(ActionInput);
				action->indices.append(node_index);
				action->indices.append(index);
				action->data = input.value;
				add_action(action);
			}
			input.value = value;
			const Type &type = types[input.type];
			const ProtoInput &proto_input = protos[node->proto].inputs[index];
			if(type.update_func) type.update_func(this, input.text, input.value, input.type);
			if(proto_input.update_func) proto_input.update_func(this, node_index, index);
			update_input_text(node_index, index);
		}
	}
	
	void ControlFlow::setInputValue(uint32_t node, uint32_t index, const String &value, bool action) {
		setInputValue(node, index, value.get(), action);
	}
	
	/*
	 */
	void ControlFlow::update_input_text(uint32_t node_index, uint32_t index) {
		NodePtr &node = nodes[node_index];
		NodeInput &input = node->inputs[index];
		if(input.text) {
			const ProtoInput &proto_input = protos[node->proto].inputs[index];
			if(input.connections || !input.value || input.value.begins("$") || input.value == proto_input.value || input.value.size() >= 8) input.text.setText(proto_input.text);
			else input.text.setText(String::format("%s %s", proto_input.text.get(), input.value.get()));
			next_update_nodes.append(node_index);
		}
	}
	
	/*
	 */
	bool ControlFlow::setInputValue(uint32_t node, const char *name, const char *value, bool action) {
		uint32_t index = findInput(node, name);
		if(index == Maxu32) {
			TS_LOGF(Error, "ControlFlow::setInputValue(): can't find \"%s\" input\n", name);
			return false;
		}
		setInputValue(node, index, value, action);
		return true;
	}
	
	bool ControlFlow::setInputValue(uint32_t node, const char *name, const String &value, bool action) {
		return setInputValue(node, name, value.get(), action);
	}
	
	bool ControlFlow::setInputValue(uint32_t node, const String &name, const String &value, bool action) {
		return setInputValue(node, name.get(), value.get(), action);
	}
	
	const String &ControlFlow::getInputValue(uint32_t node, const char *name) const {
		uint32_t index = findInput(node, name);
		if(index == Maxu32) {
			TS_LOGF(Error, "ControlFlow::getInputValue(): can't find \"%s\" input\n", name);
			return String::null;
		}
		return getInputValue(node, index);
	}
	
	const String &ControlFlow::getInputValue(uint32_t node, const String &name) const {
		return getInputValue(node, name.get());
	}
	
	/*
	 */
	void ControlFlow::setOutputType(uint32_t node_index, uint32_t index, uint32_t type, bool force) {
		NodePtr &node = nodes[node_index];
		NodeOutput &output = node->outputs[index];
		if(output.type != type || force) {
			output.type = type;
			Canvas canvas = getCanvas();
			const Type &output_type = types[output.type];
			canvas.removeElement(output.socket->getElement());
			output.socket->setElement(create_socket(canvas, output_type));
			output.socket->setColor(output.socket->getElement().getColor());
			for(OutputConnection &connection : output.connections) {
				const ProtoInput &proto_input = protos[getNodeProto(connection.node)].inputs[connection.input];
				if(proto_input.attach_func) proto_input.attach_func(this, connection.node, connection.input, node_index, index);
				update_strip(connection.strip.get(), output_type);
			}
		}
	}
	
	/*
	 */
	bool ControlFlow::setOutputType(uint32_t node, const char *name, uint32_t type, bool force) {
		uint32_t index = findOutput(node, name);
		if(index == Maxu32) {
			TS_LOGF(Error, "ControlFlow::setOutputType(): can't find \"%s\" output\n", name);
			return false;
		}
		setOutputType(node, index, type, force);
		return true;
	}
	
	bool ControlFlow::setOutputType(uint32_t node, const String &name, uint32_t type, bool force) {
		return setOutputType(node, name.get(), type, force);
	}
	
	uint32_t ControlFlow::getOutputType(uint32_t node, const char *name) const {
		uint32_t index = findOutput(node, name);
		if(index == Maxu32) {
			TS_LOGF(Error, "ControlFlow::getOutputType(): can't find \"%s\" output\n", name);
			return Maxu32;
		}
		return getOutputType(node, index);
	}
	
	uint32_t ControlFlow::getOutputType(uint32_t node, const String &name) const {
		return getOutputType(node, name.get());
	}
	
	/*
	 */
	void ControlFlow::setOutputValue(uint32_t node_index, uint32_t index, const char *value, bool action) {
		NodePtr &node = nodes[node_index];
		NodeOutput &output = node->outputs[index];
		if(output.value != value || action) {
			if(action) {
				Action *action = new Action(ActionOutput);
				action->indices.append(node_index);
				action->indices.append(index);
				action->data = output.value;
				add_action(action);
			}
			output.value = value;
			const Type &type = types[output.type];
			const ProtoOutput &proto_output = protos[node->proto].outputs[index];
			if(type.update_func) type.update_func(this, output.text, output.value, output.type);
			if(proto_output.update_func) proto_output.update_func(this, node_index, index);
		}
	}
	
	void ControlFlow::setOutputValue(uint32_t node, uint32_t index, const String &value, bool action) {
		setOutputValue(node, index, value.get(), action);
	}
	
	/*
	 */
	bool ControlFlow::setOutputValue(uint32_t node, const char *name, const char *value, bool action) {
		uint32_t index = findOutput(node, name);
		if(index == Maxu32) {
			TS_LOGF(Error, "ControlFlow::setOutputValue(): can't find \"%s\" output\n", name);
			return false;
		}
		setOutputValue(node, index, value, action);
		return true;
	}
	
	bool ControlFlow::setOutputValue(uint32_t node, const char *name, const String &value, bool action) {
		return setOutputValue(node, name, value.get(), action);
	}
	
	bool ControlFlow::setOutputValue(uint32_t node, const String &name, const String &value, bool action) {
		return setOutputValue(node, name.get(), value.get(), action);
	}
	
	const String &ControlFlow::getOutputValue(uint32_t node, const char *name) const {
		uint32_t index = findOutput(node, name);
		if(index == Maxu32) {
			TS_LOGF(Error, "ControlFlow::getOutputValue(): can't find \"%s\" output\n", name);
			return String::null;
		}
		return getOutputValue(node, index);
	}
	
	const String &ControlFlow::getOutputValue(uint32_t node, const String &name) const {
		return getOutputValue(node, name.get());
	}
	
	/*****************************************************************************\
	 *
	 * ControlFlow Connections
	 *
	\*****************************************************************************/
	
	/*
	 */
	void ControlFlow::clearConnections(uint32_t node_index) {
		NodePtr &node = nodes[node_index];
		if(node->index == Maxu32) return;
		for(uint32_t i = 0; i < node->inputs.size(); i++) {
			removeInputConnection(node_index, i);
		}
		for(uint32_t i = 0; i < node->outputs.size(); i++) {
			removeOutputConnection(node_index, i);
		}
	}
	
	/*
	 */
	uint32_t ControlFlow::addInputConnection(uint32_t node, uint32_t input, uint32_t output_node, uint32_t output_index) {
		const auto &input_node = nodes[node];
		if(input_node->index == Maxu32) return Maxu32;
		const NodeInput &node_input = input_node->inputs[input];
		addOutputConnection(output_node, output_index, node, input);
		return node_input.connections.size() - 1;
	}
	
	uint32_t ControlFlow::addInputConnection(uint32_t node, const char *input, uint32_t output_node, const char *output_name) {
		uint32_t input_index = findInput(node, input);
		if(input_index == Maxu32) {
			TS_LOGF(Error, "ControlFlow::addInputConnection(): can't find \"%s\" input\n", input);
			return Maxu32;
		}
		uint32_t output_index = findOutput(output_node, output_name);
		if(output_index == Maxu32) {
			TS_LOGF(Error, "ControlFlow::addInputConnection(): can't find \"%s\" output\n", output_name);
			return false;
		}
		return addInputConnection(node, input_index, output_node, output_index);
	}
	
	uint32_t ControlFlow::addInputConnection(uint32_t node, const String &input, uint32_t output_node, const String &output_name) {
		return addInputConnection(node, input.get(), output_node, output_name.get());
	}
	
	
	/*
	 */
	bool ControlFlow::isInputConnected(uint32_t node, uint32_t input, uint32_t output_node, uint32_t output_index) const {
		for(const InputConnection &input_connection : nodes[node]->inputs[input].connections) {
			if(input_connection.node != output_node) continue;
			if(input_connection.output != output_index) continue;
			return true;
		}
		return false;
	}
	
	bool ControlFlow::isInputConnected(uint32_t node, const char *input, uint32_t output_node, const char *output_name) const {
		uint32_t input_index = findInput(node, input);
		if(input_index == Maxu32) {
			TS_LOGF(Error, "ControlFlow::isInputConnected(): can't find \"%s\" input\n", input);
			return false;
		}
		uint32_t output_index = findOutput(output_node, output_name);
		if(output_index == Maxu32) {
			TS_LOGF(Error, "ControlFlow::isInputConnected(): can't find \"%s\" output\n", output_name);
			return false;
		}
		return isInputConnected(node, input_index, output_node, output_index);
	}
	
	bool ControlFlow::isInputConnected(uint32_t node, const String &input, uint32_t output_node, const String &output_name) const {
		return isInputConnected(node, input.get(), output_node, output_name.get());
	}
	
	/*
	 */
	void ControlFlow::removeInputConnection(uint32_t node, uint32_t input, uint32_t output_node, uint32_t output_index) {
		bool is_removed = false;
		auto &input_connections = nodes[node]->inputs[input].connections;
		for(uint32_t i = input_connections.size(); i > 0; i--) {
			InputConnection &input_connection = input_connections[i - 1];
			if(input_connection.node != output_node && output_node != Maxu32) continue;
			if(input_connection.output != output_index && output_index != Maxu32) continue;
			auto &output_connections = nodes[input_connection.node]->outputs[input_connection.output].connections;
			for(uint32_t j = output_connections.size(); j > 0; j--) {
				OutputConnection &output_connection = output_connections[j - 1];
				if(output_connection.node == node && output_connection.input == input) {
					removed_elements.append(output_connection.strip.release());
					output_connections.remove(j - 1);
					const ProtoOutput &proto_output = protos[getNodeProto(input_connection.node)].outputs[input_connection.output];
					if(proto_output.attach_func && !is_clear) proto_output.attach_func(this, input_connection.node, input_connection.output, Maxu32, Maxu32);
				}
			}
			input_connections.remove(i - 1);
			update_input_text(node, input);
			is_changed = true;
			is_removed = true;
		}
		if(is_removed) {
			const ProtoInput &proto_input = protos[getNodeProto(node)].inputs[input];
			if(proto_input.attach_func && !is_clear) proto_input.attach_func(this, node, input, Maxu32, Maxu32);
		}
	}
	
	/*
	 */
	uint32_t ControlFlow::getNumInputConnections(uint32_t node, const char *name) const {
		if(name == nullptr) {
			uint32_t num_connections = 0;
			for(const NodeInput &input : nodes[node]->inputs) {
				num_connections += input.connections.size();
			}
			return num_connections;
		}
		uint32_t index = findInput(node, name);
		if(index == Maxu32) {
			TS_LOGF(Error, "ControlFlow::getNumInputConnections(): can't find \"%s\" input\n", name);
			return 0;
		}
		return getNumInputConnections(node, index);
	}
	
	/*
	 */
	uint32_t ControlFlow::getInputConnectionType(uint32_t node, uint32_t input, uint32_t index) const {
		uint32_t output_node = getInputConnectionNode(node, input, index);
		uint32_t output_index = getInputConnectionOutput(node, input, index);
		return getOutputType(output_node, output_index);
	}
	
	const String &ControlFlow::getInputConnectionValue(uint32_t node, uint32_t input, uint32_t index) const {
		uint32_t output_node = getInputConnectionNode(node, input, index);
		uint32_t output_index = getInputConnectionOutput(node, input, index);
		return getOutputValue(output_node, output_index);
	}
	
	/*
	 */
	ControlElement *ControlFlow::getInputConnectionStrip(uint32_t node, uint32_t input, uint32_t index) {
		const InputConnection &connection = nodes[node]->inputs[input].connections[index];
		auto &connections = nodes[connection.node]->outputs[connection.output].connections;
		for(uint32_t i = 0; i < connections.size(); i++) {
			if(connections[i].input == input) return connections[i].strip.get();
		}
		return nullptr;
	}
	
	const ControlElement *ControlFlow::getInputConnectionStrip(uint32_t node, uint32_t input, uint32_t index) const {
		const InputConnection &connection = nodes[node]->inputs[input].connections[index];
		const auto &connections = nodes[connection.node]->outputs[connection.output].connections;
		for(uint32_t i = 0; i < connections.size(); i++) {
			if(connections[i].input == input) return connections[i].strip.get();
		}
		return nullptr;
	}
	
	/*
	 */
	uint32_t ControlFlow::addOutputConnection(uint32_t output_node_index, uint32_t output_index, uint32_t input_node_index, uint32_t input_index) {
		
		// connection nodes
		auto &output_node = nodes[output_node_index];
		auto &input_node = nodes[input_node_index];
		if(output_node->index == Maxu32) return Maxu32;
		if(input_node->index == Maxu32) return Maxu32;
		
		// output node
		const Proto &output_proto = protos[output_node->proto];
		NodeOutput &node_output = output_node->outputs[output_index];
		const ProtoOutput &proto_output = output_proto.outputs[output_index];
		if(!proto_output.is_multi) removeOutputConnection(output_node_index, output_index);
		
		// input node
		const Proto &input_proto = protos[input_node->proto];
		NodeInput &node_input = input_node->inputs[input_index];
		const ProtoInput &proto_input = input_proto.inputs[input_index];
		if(!proto_input.is_multi) removeInputConnection(input_node_index, input_index);
		
		// create output connection
		OutputConnection output_connection;
		output_connection.node = input_node_index;
		output_connection.input = input_index;
		output_connection.strip = makeAutoPtr(create_strip(types[node_output.type]));
		node_output.connections.append(output_connection);
		
		// create input connection
		InputConnection input_connection;
		input_connection.node = output_node_index;
		input_connection.output = output_index;
		node_input.connections.append(input_connection);
		
		// attachment callbacks
		bool ret = true;
		if(proto_output.attach_func) ret &= proto_output.attach_func(this, output_node_index, output_index, input_node_index, input_index);
		if(proto_input.attach_func) ret &= proto_input.attach_func(this, input_node_index, input_index, output_node_index, output_index);
		
		// remove connection
		if(!ret) {
			removeOutputConnection(output_node_index, output_index, input_node_index, input_index);
			return Maxu32;
		}
		
		// update input text
		update_input_text(input_node_index, input_index);
		
		// update node
		update_nodes.append(output_node_index);
		
		// changed flag
		is_changed = true;
		
		// return connection index
		return node_output.connections.size() - 1;
	}
	
	uint32_t ControlFlow::addOutputConnection(uint32_t node, const char *output, uint32_t input_node, const char *input_name) {
		uint32_t output_index = findOutput(node, output);
		if(output_index == Maxu32) {
			TS_LOGF(Error, "ControlFlow::addOutputConnection(): can't find \"%s\" output\n", output);
			return Maxu32;
		}
		uint32_t input_index = findInput(input_node, input_name);
		if(input_index == Maxu32) {
			TS_LOGF(Error, "ControlFlow::addOutputConnection(): can't find \"%s\" input\n", input_name);
			return Maxu32;
		}
		return addOutputConnection(node, output_index, input_node, input_index);
	}
	
	uint32_t ControlFlow::addOutputConnection(uint32_t node, const String &output, uint32_t input_node, const String &input_name) {
		return addOutputConnection(node, output.get(), input_node, input_name.get());
	}
	
	/*
	 */
	bool ControlFlow::isOutputConnected(uint32_t node, uint32_t output, uint32_t input_node, uint32_t input_index) const {
		for(const OutputConnection &output_connection : nodes[node]->outputs[output].connections) {
			if(output_connection.node != input_node) continue;
			if(output_connection.input != input_index) continue;
			return true;
		}
		return false;
	}
	
	bool ControlFlow::isOutputConnected(uint32_t node, const char *output, uint32_t input_node, const char *input_name) const {
		uint32_t output_index = findOutput(node, output);
		if(output_index == Maxu32) {
			TS_LOGF(Error, "ControlFlow::isOutputConnected(): can't find \"%s\" output\n", output);
			return false;
		}
		uint32_t input_index = findInput(input_node, input_name);
		if(input_index == Maxu32) {
			TS_LOGF(Error, "ControlFlow::isOutputConnected(): can't find \"%s\" input\n", input_name);
			return false;
		}
		return isOutputConnected(node, output_index, input_node, input_index);
	}
	
	bool ControlFlow::isOutputConnected(uint32_t node, const String &output, uint32_t input_node, const String &input_name) const {
		return isOutputConnected(node, output.get(), input_node, input_name.get());
	}
	
	/*
	 */
	void ControlFlow::removeOutputConnection(uint32_t node, uint32_t output, uint32_t input_node, uint32_t input_index) {
		bool is_removed = false;
		auto &output_connections = nodes[node]->outputs[output].connections;
		for(uint32_t i = output_connections.size(); i > 0; i--) {
			OutputConnection &output_connection = output_connections[i - 1];
			if(output_connection.node != input_node && input_node != Maxu32) continue;
			if(output_connection.input != input_index && input_index != Maxu32) continue;
			auto &input_connections = nodes[output_connection.node]->inputs[output_connection.input].connections;
			for(uint32_t j = input_connections.size(); j > 0; j--) {
				InputConnection &input_connection = input_connections[j - 1];
				if(input_connection.node == node && input_connection.output == output) {
					input_connections.remove(j - 1);
					const ProtoInput &proto_input = protos[getNodeProto(output_connection.node)].inputs[output_connection.input];
					if(proto_input.attach_func && !is_clear) proto_input.attach_func(this, output_connection.node, output_connection.input, Maxu32, Maxu32);
					update_input_text(output_connection.node, output_connection.input);
				}
			}
			removed_elements.append(output_connection.strip.release());
			output_connections.remove(i - 1);
			is_changed = true;
			is_removed = true;
		}
		if(is_removed) {
			const ProtoOutput &proto_output = protos[getNodeProto(node)].outputs[output];
			if(proto_output.attach_func && !is_clear) proto_output.attach_func(this, node, output, Maxu32, Maxu32);
		}
	}
	
	/*
	 */
	uint32_t ControlFlow::getNumOutputConnections(uint32_t node, const char *name) const {
		if(name == nullptr) {
			uint32_t num_connections = 0;
			for(const NodeOutput &output : nodes[node]->outputs) {
				num_connections += output.connections.size();
			}
			return num_connections;
		}
		uint32_t index = findOutput(node, name);
		if(index == Maxu32) {
			TS_LOGF(Error, "ControlFlow::getNumOutputConnections(): can't find \"%s\" input\n", name);
			return 0;
		}
		return getNumOutputConnections(node, index);
	}
	
	/*
	 */
	uint32_t ControlFlow::getOutputConnectionType(uint32_t node, uint32_t output, uint32_t index) const {
		uint32_t input_node = getOutputConnectionNode(node, output, index);
		uint32_t input_index = getOutputConnectionInput(node, output, index);
		return getInputType(input_node, input_index);
	}
	
	const String &ControlFlow::getOutputConnectionValue(uint32_t node, uint32_t output, uint32_t index) const {
		uint32_t input_node = getOutputConnectionNode(node, output, index);
		uint32_t input_index = getOutputConnectionInput(node, output, index);
		return getInputValue(input_node, input_index);
	}
	
	/*****************************************************************************\
	 *
	 * ControlFlow Traversal
	 *
	\*****************************************************************************/
	
	/*
	 */
	void ControlFlow::propagateInputValue(uint32_t node, uint32_t index) {
		const NodeInput &input = nodes[node]->inputs[index];
		String value = getProtoInputValue(getNodeProto(node), index);
		for(const InputConnection &connection : input.connections) {
			value = getOutputValue(connection.node, connection.output);
			break;
		}
		setInputValue(node, index, value);
	}
	
	void ControlFlow::propagateInputValues(uint32_t node) {
		for(uint32_t i = 0; i < nodes[node]->inputs.size(); i++) {
			propagateInputValue(node, i);
		}
	}
	
	/*
	 */
	void ControlFlow::propagateOutputValue(uint32_t node, uint32_t index) {
		const NodeOutput &output = nodes[node]->outputs[index];
		for(const OutputConnection &connection : output.connections) {
			setInputValue(connection.node, connection.input, output.value);
		}
	}
	
	void ControlFlow::propagateOutputValues(uint32_t node) {
		for(uint32_t i = 0; i < nodes[node]->outputs.size(); i++) {
			propagateOutputValue(node, i);
		}
	}
	
	/*
	 */
	void ControlFlow::getInputBranch(uint32_t node, uint32_t index, Array<uint32_t> &node_indices) {
		frame++;
		Array<uint32_t> indices;
		if(index != Maxu32) {
			const NodeInput &input = nodes[node]->inputs[index];
			for(const InputConnection &connection : input.connections) {
				indices.append(connection.node);
			}
		} else {
			for(const NodeInput &input : nodes[node]->inputs) {
				for(const InputConnection &connection : input.connections) {
					indices.append(connection.node);
				}
			}
		}
		for(uint32_t i = 0; i < indices.size(); i++) {
			NodePtr &node = nodes[indices[i]];
			if(node->frame == frame) continue;
			node->frame = frame;
			node_indices.append(indices[i]);
			for(const NodeInput &input : node->inputs) {
				for(const InputConnection &connection : input.connections) {
					indices.append(connection.node);
				}
			}
		}
	}
	
	bool ControlFlow::getInputBranch(uint32_t node, const char *name, Array<uint32_t> &node_indices) {
		uint32_t index = findInput(node, name);
		if(index == Maxu32) {
			TS_LOGF(Error, "ControlFlow::getInputBranch(): can't find \"%s\" input\n", name);
			return false;
		}
		getInputBranch(node, index, node_indices);
		return true;
	}
	
	/*
	 */
	void ControlFlow::getOutputBranch(uint32_t node, uint32_t index, Array<uint32_t> &node_indices) {
		frame++;
		Array<uint32_t> indices;
		if(index != Maxu32) {
			const NodeOutput &output = nodes[node]->outputs[index];
			for(const OutputConnection &connection : output.connections) {
				indices.append(connection.node);
			}
		} else {
			for(const NodeOutput &output : nodes[node]->outputs) {
				for(const OutputConnection &connection : output.connections) {
					indices.append(connection.node);
				}
			}
		}
		for(uint32_t i = 0; i < indices.size(); i++) {
			NodePtr &node = nodes[indices[i]];
			if(node->frame == frame) continue;
			node->frame = frame;
			node_indices.append(indices[i]);
			for(const NodeOutput &output : node->outputs) {
				for(const OutputConnection &connection : output.connections) {
					indices.append(connection.node);
				}
			}
		}
	}
	
	bool ControlFlow::getOutputBranch(uint32_t node, const char *name, Array<uint32_t> &node_indices) {
		uint32_t index = findOutput(node, name);
		if(index == Maxu32) {
			TS_LOGF(Error, "ControlFlow::getOutputBranch(): can't find \"%s\" output\n", name);
			return false;
		}
		getOutputBranch(node, index, node_indices);
		return true;
	}
	
	/*
	 */
	void ControlFlow::traverseNodes(uint32_t node, const TraversalCallback &func) {
		
		// update frame
		frame++;
		
		// traverse index
		struct Index {
			Index() { }
			Index(uint32_t node, uint32_t parent, int32_t distance, uint32_t index) : node(node), parent(parent), distance(distance), index(index) { }
			uint32_t node;
			uint32_t parent;
			int32_t distance;
			uint32_t index;
		};
		
		// node traversal
		Array<Index> node_indices;
		Array<Index> traverse_indices;
		node_indices.append(Index(node, Maxu32, 0, Maxu32));
		for(uint32_t i = 0; i < node_indices.size(); i++) {
			Index index = node_indices[i];
			NodePtr &node = nodes[index.node];
			if(node->index == Maxu32) continue;
			
			// distance to the node
			int32_t distance = index.distance + 1;
			if(node->frame != frame) node->distance = Vector2i(distance);
			else node->distance = Vector2i(max(node->distance.x, distance), min(node->distance.y, distance));
			
			// traverse indices
			if(node->frame != frame) traverse_indices.append(index);
			
			// node outputs
			for(const NodeOutput &output : node->outputs) {
				if(isProtoFinalOutput(node->proto, output.index)) continue;
				for(const OutputConnection &connection : output.connections) {
					if(isProtoFinalInput(getNodeProto(connection.node), connection.input)) continue;
					if(node->frame == frame) {
						bool is_parent = false;
						uint32_t parent = index.index;
						while(parent != Maxu32) {
							if(node_indices[parent].node == connection.node) is_parent = true;
							parent = node_indices[parent].index;
						}
						if(is_parent) continue;
					}
					node_indices.append(Index(connection.node, index.node, distance, i));
				}
			}
			
			node->frame = frame;
			node->traverse = frame;
		}
		
		// inverse node traversal
		node_indices.clear();
		for(Index &index : traverse_indices) {
			node_indices.append(Index(index.node, Maxu32, index.distance, Maxu32));
		}
		for(uint32_t i = 0; i < node_indices.size(); i++) {
			Index index = node_indices[i];
			NodePtr &node = nodes[index.node];
			if(node->index == Maxu32) continue;
			
			// distance to the node
			int32_t distance = index.distance - 1;
			if(node->frame != frame) node->distance = Vector2i(distance);
			else if(node->traverse != frame) node->distance = Vector2i(min(node->distance.x, distance), min(node->distance.y, distance));
			
			// traverse indices
			if(node->frame != frame) traverse_indices.append(index);
			
			// node inputs
			for(const NodeInput &input : node->inputs) {
				if(isProtoFinalInput(node->proto, input.index)) continue;
				for(const InputConnection &connection : input.connections) {
					if(isProtoFinalOutput(getNodeProto(connection.node), connection.output)) {
						NodePtr &node = nodes[connection.node];
						node->traverse = frame - 1;
					}
					if(nodes[connection.node]->traverse == frame) continue;
					if(node->frame == frame) {
						bool is_parent = false;
						uint32_t parent = index.index;
						while(parent != Maxu32) {
							if(node_indices[parent].node == connection.node) is_parent = true;
							parent = node_indices[parent].index;
						}
						if(is_parent) continue;
					}
					node_indices.append(Index(connection.node, index.node, distance, i));
				}
			}
			
			node->frame = frame;
		}
		
		// sort nodes by distance
		for(Index &index : traverse_indices) {
			const Vector2i &distance = nodes[index.node]->distance;
			index.distance = distance.x * Maxi16 + distance.y;
		}
		quickSort(traverse_indices.get(), traverse_indices.size(), makeQuickCompare<Index>([](const Index &i0, const Index &i1) {
			if(i0.distance > i1.distance) return 1;
			if(i0.distance < i1.distance) return -1;
			return 0;
		}));
		
		// traverse nodes
		for(const Index &index : traverse_indices) {
			
			// update node
			updateNode(index.node, false);
			
			// traverse callback
			if(func) func(this, index.node, index.parent);
			else propagateOutputValues(index.node);
		}
	}
	
	/*
	 */
	void ControlFlow::itraverseNodes(uint32_t node, const TraversalCallback &func) {
		
		// update frame
		frame++;
		
		// traverse index
		struct Index {
			Index() { }
			Index(uint32_t node, uint32_t parent, int32_t distance, uint32_t index) : node(node), parent(parent), distance(distance), index(index) { }
			uint32_t node;
			uint32_t parent;
			int32_t distance;
			uint32_t index;
		};
		
		// inverse node traversal
		Array<Index> node_indices;
		Array<Index> traverse_indices;
		node_indices.append(Index(node, Maxu32, 0, Maxu32));
		for(uint32_t i = 0; i < node_indices.size(); i++) {
			Index index = node_indices[i];
			NodePtr &node = nodes[index.node];
			if(node->index == Maxu32) continue;
			
			// distance to the node
			int32_t distance = index.distance + 1;
			if(node->frame != frame) node->distance = Vector2i(distance);
			else node->distance = Vector2i(max(node->distance.x, distance), min(node->distance.y, distance));
			
			// traverse indices
			if(node->frame != frame) traverse_indices.append(index);
			
			// node inputs
			for(const NodeInput &input : node->inputs) {
				if(isProtoFinalInput(node->proto, input.index)) continue;
				for(const InputConnection &connection : input.connections) {
					if(isProtoFinalOutput(getNodeProto(connection.node), connection.output)) continue;
					if(node->frame == frame) {
						bool is_parent = false;
						uint32_t parent = index.index;
						while(parent != Maxu32) {
							if(node_indices[parent].node == connection.node) is_parent = true;
							parent = node_indices[parent].index;
						}
						if(is_parent) continue;
					}
					node_indices.append(Index(connection.node, index.node, distance, i));
				}
			}
			
			node->frame = frame;
		}
		
		// sort nodes by distance
		for(Index &index : traverse_indices) {
			const Vector2i &distance = nodes[index.node]->distance;
			index.distance = distance.x * Maxi16 + distance.y;
		}
		quickSort(traverse_indices.get(), traverse_indices.size(), makeQuickCompare<Index>([](const Index &i0, const Index &i1) {
			if(i0.distance > i1.distance) return 1;
			if(i0.distance < i1.distance) return -1;
			return 0;
		}));
		
		// traverse nodes
		for(uint32_t i = traverse_indices.size(); i > 0; i--) {
			const Index &index = traverse_indices[i - 1];
			
			// update node
			updateNode(index.node, true);
			
			// traverse callback
			if(func) func(this, index.node, index.parent);
			else propagateInputValues(index.node);
		}
	}
	
	/*****************************************************************************\
	 *
	 * ControlFlow Utils
	 *
	\*****************************************************************************/
	
	/*
	 */
	Vector2f ControlFlow::get_mouse_position(const ControlRoot &root) const {
		return floor(root.getMouse() / flow_area.getScale() - flow_area.getControlsOffset() - flow_area.getControlsSize() * 0.5f + 0.5f);
	}
	
	/*
	 */
	TS_INLINE const ControlFlow::Type &ControlFlow::get_node_input_type(uint32_t node, uint32_t input) const {
		return types[nodes[node]->inputs[input].type];
	}
	
	TS_INLINE const ControlFlow::Type &ControlFlow::get_node_output_type(uint32_t node, uint32_t output) const {
		return types[nodes[node]->outputs[output].type];
	}
	
	TS_INLINE const ControlFlow::TypeMask &ControlFlow::get_node_input_mask(uint32_t node, uint32_t input) const {
		return protos[nodes[node]->proto].inputs[input].mask;
	}
	
	TS_INLINE const ControlFlow::TypeMask &ControlFlow::get_node_output_mask(uint32_t node, uint32_t output) const {
		return protos[nodes[node]->proto].outputs[output].mask;
	}
	
	/*
	 */
	bool ControlFlow::is_compatible_types(const Type &type_0, const Type &type_1, const TypeMask &mask_0, const TypeMask &mask_1) const {
		if(TypeMask(type_0.index) & (type_1.input_mask | mask_1)) return true;
		if((TypeMask(type_0.index) | mask_0) & type_1.input_mask) return true;
		if((type_0.output_mask | mask_0) & TypeMask(type_1.index)) return true;
		if(type_0.output_mask & (TypeMask(type_1.index) | mask_1)) return true;
		if(type_0.index == type_1.index) return true;
		if(mask_0 & mask_1) return true;
		return false;
	}
	
	/*
	 */
	CanvasElement ControlFlow::create_socket(Canvas &canvas, const Type &type) {
		
		CanvasElement canvas_element;
		
		// socket radius
		float32_t radius = getRadius();
		
		// create circle shape
		if(type.shape == ShapeCircle) {
			CanvasEllipse ellipse = CanvasEllipse(canvas);
			ellipse.setStrokeStyle(type.stroke_style);
			ellipse.setGradientStyle(type.gradient_style);
			if(type.gradient_style) ellipse.setMode(CanvasElement::ModeGradient);
			ellipse.setRadius(radius);
			canvas_element = ellipse;
		}
		// create hexagon shape
		else if(type.shape == ShapeHexagon) {
			float32_t offset = radius * sqrt(3.0f) * 0.5f;
			float32_t height = radius * 0.5f;
			Vector2f p0 = Vector2f(0.0f, radius);
			Vector2f p1 = Vector2f(-offset,  height);
			Vector2f p2 = Vector2f(-offset, -height);
			Vector2f p3 = Vector2f(0.0f, -radius);
			Vector2f p4 = Vector2f( offset, -height);
			Vector2f p5 = Vector2f( offset,  height);
			CanvasShape shape = CanvasShape(canvas);
			shape.setStrokeStyle(type.stroke_style);
			shape.setGradientStyle(type.gradient_style);
			if(type.gradient_style) shape.setMode(CanvasElement::ModeGradient);
			shape.addPosition(p0); shape.addPosition(p0); shape.addPosition(p1);
			shape.addPosition(p1); shape.addPosition(p1); shape.addPosition(p2);
			shape.addPosition(p2); shape.addPosition(p2); shape.addPosition(p3);
			shape.addPosition(p3); shape.addPosition(p3); shape.addPosition(p4);
			shape.addPosition(p4); shape.addPosition(p4); shape.addPosition(p5);
			shape.addPosition(p5); shape.addPosition(p5); shape.addPosition(p0);
			canvas_element = shape;
		}
		// create pentagon shape
		else if(type.shape == ShapePentagon) {
			Vector2f p0 = Vector2f(0.0f, radius);
			Vector2f p1 = Vector2f( 0.951057f,  0.309017f) * radius;
			Vector2f p2 = Vector2f( 0.587785f, -0.809017f) * radius;
			Vector2f p3 = Vector2f(-0.587785f, -0.809017f) * radius;
			Vector2f p4 = Vector2f(-0.951056f,  0.309017f) * radius;
			CanvasShape shape = CanvasShape(canvas);
			shape.setStrokeStyle(type.stroke_style);
			shape.setGradientStyle(type.gradient_style);
			if(type.gradient_style) shape.setMode(CanvasElement::ModeGradient);
			shape.addPosition(p0); shape.addPosition(p0); shape.addPosition(p1);
			shape.addPosition(p1); shape.addPosition(p1); shape.addPosition(p2);
			shape.addPosition(p2); shape.addPosition(p2); shape.addPosition(p3);
			shape.addPosition(p3); shape.addPosition(p3); shape.addPosition(p4);
			shape.addPosition(p4); shape.addPosition(p4); shape.addPosition(p0);
			canvas_element = shape;
		}
		// create square shape
		else if(type.shape == ShapeSquare) {
			CanvasRect rect = CanvasRect(canvas);
			rect.setStrokeStyle(type.stroke_style);
			rect.setGradientStyle(type.gradient_style);
			if(type.gradient_style) rect.setMode(CanvasElement::ModeGradient);
			rect.setSize(radius * 2.0f, radius * 2.0f);
			canvas_element = rect;
		}
		// create diamond shape
		else if(type.shape == ShapeDiamond) {
			CanvasShape shape = CanvasShape(canvas);
			shape.setStrokeStyle(type.stroke_style);
			shape.setGradientStyle(type.gradient_style);
			if(type.gradient_style) shape.setMode(CanvasElement::ModeGradient);
			create_rect(shape, Vector2f(0.0f, radius), Vector2f(-radius, 0.0f), Vector2f(0.0f, -radius), Vector2f(radius, 0.0f));
			canvas_element = shape;
		}
		// create triangle shape
		else if(type.shape == ShapeTriangle) {
			CanvasTriangle triangle = CanvasTriangle(canvas);
			triangle.setStrokeStyle(type.stroke_style);
			triangle.setGradientStyle(type.gradient_style);
			if(type.gradient_style) triangle.setMode(CanvasElement::ModeGradient);
			triangle.setPosition0(0.0f, radius);
			triangle.setPosition1(-radius, -radius * 0.75f);
			triangle.setPosition2( radius, -radius * 0.75f);
			canvas_element = triangle;
		}
		// create arrow shape
		else if(type.shape == ShapeArrow) {
			CanvasTriangle triangle = CanvasTriangle(canvas);
			triangle.setStrokeStyle(type.stroke_style);
			triangle.setGradientStyle(type.gradient_style);
			if(type.gradient_style) triangle.setMode(CanvasElement::ModeGradient);
			triangle.setPosition0(radius, 0.0f);
			triangle.setPosition1(-radius * 0.75f, -radius);
			triangle.setPosition2(-radius * 0.75f,  radius);
			canvas_element = triangle;
		}
		// create ring shape
		else if(type.shape == ShapeRing) {
			float32_t offset = radius - floor(radius / 3.0f + 0.5f);
			CanvasShape shape = CanvasShape(canvas);
			shape.setStrokeStyle(type.stroke_style);
			shape.setGradientStyle(type.gradient_style);
			if(type.gradient_style) shape.setMode(CanvasElement::ModeGradient);
			for(uint32_t i = 0; i < 8; i++) {
				float32_t a0 = Pi2 * (i + 0.0f) / 8.0f;
				float32_t a1 = Pi2 * (i + 0.5f) / 8.0f;
				float32_t a2 = Pi2 * (i + 1.0f) / 8.0f;
				shape.addPosition(Vector2f(sin(a0), cos(a0)) * radius);
				shape.addPosition(Vector2f(sin(a1), cos(a1)) * (radius * 1.1f));
				shape.addPosition(Vector2f(sin(a2), cos(a2)) * radius);
			}
			for(uint32_t i = 0; i < 8; i++) {
				float32_t a0 = -Pi2 * (i + 0.0f) / 8.0f;
				float32_t a1 = -Pi2 * (i + 0.5f) / 8.0f;
				float32_t a2 = -Pi2 * (i + 1.0f) / 8.0f;
				shape.addPosition(Vector2f(sin(a0), cos(a0)) * offset);
				shape.addPosition(Vector2f(sin(a1), cos(a1)) * (offset * 1.1f));
				shape.addPosition(Vector2f(sin(a2), cos(a2)) * offset);
			}
			canvas_element = shape;
		}
		// create frame shape
		else if(type.shape == ShapeFrame) {
			float32_t offset = radius - floor(radius / 3.0f + 0.5f);
			CanvasShape shape = CanvasShape(canvas);
			shape.setStrokeStyle(type.stroke_style);
			shape.setGradientStyle(type.gradient_style);
			if(type.gradient_style) shape.setMode(CanvasElement::ModeGradient);
			create_rect(shape, Vector2f(radius, radius), Vector2f(-radius, radius), Vector2f(-radius, -radius), Vector2f(radius, -radius));
			shape.setNumPositions(12 * 3 * 1);
			create_rect(shape, Vector2f(offset, offset), Vector2f(offset, -offset), Vector2f(-offset, -offset), Vector2f(-offset, offset));
			shape.setNumPositions(12 * 3 * 2);
			canvas_element = shape;
		}
		// create delta shape
		else if(type.shape == ShapeDelta) {
			float32_t offset = radius - floor(radius / 3.0f + 0.5f);
			CanvasShape shape = CanvasShape(canvas);
			shape.setStrokeStyle(type.stroke_style);
			shape.setGradientStyle(type.gradient_style);
			if(type.gradient_style) shape.setMode(CanvasElement::ModeGradient);
			shape.addPosition(0.0f, radius); shape.addPosition(0.0f, radius); shape.addPosition(-radius, -radius * 0.75f);
			shape.addPosition(-radius, -radius * 0.75f); shape.addPosition(-radius, -radius * 0.75f); shape.addPosition( radius, -radius * 0.75f);
			shape.addPosition( radius, -radius * 0.75f); shape.addPosition( radius, -radius * 0.75f); shape.addPosition( 0.0f, radius);
			shape.addPosition(0.0f, offset); shape.addPosition(0.0f, offset); shape.addPosition(offset, -offset * 0.8f);
			shape.addPosition( offset, -offset * 0.8f); shape.addPosition( offset, -offset * 0.8f); shape.addPosition(-offset, -offset * 0.8f);
			shape.addPosition(-offset, -offset * 0.8f); shape.addPosition(-offset, -offset * 0.8f); shape.addPosition( 0.0f, offset);
			canvas_element = shape;
		}
		// create nabla shape
		else if(type.shape == ShapeNabla) {
			float32_t offset = radius - floor(radius / 3.0f + 0.5f);
			CanvasShape shape = CanvasShape(canvas);
			shape.setStrokeStyle(type.stroke_style);
			shape.setGradientStyle(type.gradient_style);
			if(type.gradient_style) shape.setMode(CanvasElement::ModeGradient);
			shape.addPosition(0.0f, -radius); shape.addPosition(0.0f, -radius); shape.addPosition(radius, radius * 0.75f);
			shape.addPosition( radius, radius * 0.75f); shape.addPosition( radius, radius * 0.75f); shape.addPosition(-radius, radius * 0.75f);
			shape.addPosition(-radius, radius * 0.75f); shape.addPosition(-radius, radius * 0.75f); shape.addPosition( 0.0f, -radius);
			shape.addPosition(0.0f, -offset); shape.addPosition(0.0f, -offset); shape.addPosition(-offset, offset * 0.8f);
			shape.addPosition(-offset, offset * 0.8f); shape.addPosition(-offset, offset * 0.8f); shape.addPosition(offset, offset * 0.8f);
			shape.addPosition( offset, offset * 0.8f); shape.addPosition( offset, offset * 0.8f); shape.addPosition(0.0f, -offset);
			canvas_element = shape;
		}
		// create equal shape
		else if(type.shape == ShapeEqual) {
			float32_t width = floor(radius / 6.0f + 0.5f);
			float32_t offset = floor(radius / 3.0f + 0.5f);
			CanvasShape shape = CanvasShape(canvas);
			shape.setStrokeStyle(type.stroke_style);
			shape.setGradientStyle(type.gradient_style);
			if(type.gradient_style) shape.setMode(CanvasElement::ModeGradient);
			create_rect(shape, Vector2f(-radius, width - offset), Vector2f(-radius, -width - offset), Vector2f(radius, -width - offset), Vector2f(radius, width - offset));
			create_rect(shape, Vector2f(-radius, width + offset), Vector2f(-radius, -width + offset), Vector2f(radius, -width + offset), Vector2f(radius, width + offset));
			canvas_element = shape;
		}
		// create cross shape
		else if(type.shape == ShapeCross) {
			float32_t width = floor(radius / 6.0f + 0.5f);
			CanvasShape shape = CanvasShape(canvas);
			shape.setStrokeStyle(type.stroke_style);
			shape.setGradientStyle(type.gradient_style);
			if(type.gradient_style) shape.setMode(CanvasElement::ModeGradient);
			Matrix3x2f m0 = Matrix3x2f::rotate(-45.0f);
			Matrix3x2f m1 = Matrix3x2f::rotate( 45.0f);
			create_rect(shape, m0 * Vector2f(-width, radius), m0 * Vector2f(-width, -radius), m0 * Vector2f(width, -radius), m0 * Vector2f(width, radius));
			create_rect(shape, m1 * Vector2f(-width, radius), m1 * Vector2f(-width, -radius), m1 * Vector2f(width, -radius), m1 * Vector2f(width, radius));
			canvas_element = shape;
		}
		// create plus shape
		else if(type.shape == ShapePlus) {
			float32_t width = radius / 6.0f;
			CanvasShape shape = CanvasShape(canvas);
			shape.setStrokeStyle(type.stroke_style);
			shape.setGradientStyle(type.gradient_style);
			if(type.gradient_style) shape.setMode(CanvasElement::ModeGradient);
			create_rect(shape, Vector2f(-width, radius), Vector2f(-width, -radius), Vector2f(width, -radius), Vector2f(width, radius));
			create_rect(shape, Vector2f(-radius, width), Vector2f(-radius, -width), Vector2f(radius, -width), Vector2f(radius, width));
			canvas_element = shape;
		}
		// create hash shape
		else if(type.shape == ShapeHash) {
			float32_t width = floor(radius / 6.0f + 0.5f);
			float32_t offset = floor(radius / 3.0f + 0.5f);
			CanvasShape shape = CanvasShape(canvas);
			shape.setStrokeStyle(type.stroke_style);
			shape.setGradientStyle(type.gradient_style);
			if(type.gradient_style) shape.setMode(CanvasElement::ModeGradient);
			create_rect(shape, Vector2f(-width - offset, radius), Vector2f(-width - offset, -radius), Vector2f(width - offset, -radius), Vector2f(width - offset, radius));
			create_rect(shape, Vector2f(-width + offset, radius), Vector2f(-width + offset, -radius), Vector2f(width + offset, -radius), Vector2f(width + offset, radius));
			create_rect(shape, Vector2f(-radius, width - offset), Vector2f(-radius, -width - offset), Vector2f(radius, -width - offset), Vector2f(radius, width - offset));
			create_rect(shape, Vector2f(-radius, width + offset), Vector2f(-radius, -width + offset), Vector2f(radius, -width + offset), Vector2f(radius, width + offset));
			canvas_element = shape;
		}
		// create star shape
		else if(type.shape == ShapeStar) {
			float32_t width = floor(radius / 6.0f + 0.5f);
			CanvasShape shape = CanvasShape(canvas);
			shape.setStrokeStyle(type.stroke_style);
			shape.setGradientStyle(type.gradient_style);
			if(type.gradient_style) shape.setMode(CanvasElement::ModeGradient);
			Matrix3x2f m0 = Matrix3x2f::rotate(-60.0f);
			Matrix3x2f m1 = Matrix3x2f::rotate( 60.0f);
			create_rect(shape, Vector2f(-width, radius), Vector2f(-width, -radius), Vector2f(width, -radius), Vector2f(width, radius));
			create_rect(shape, m0 * Vector2f(-width, radius), m0 * Vector2f(-width, -radius), m0 * Vector2f(width, -radius), m0 * Vector2f(width, radius));
			create_rect(shape, m1 * Vector2f(-width, radius), m1 * Vector2f(-width, -radius), m1 * Vector2f(width, -radius), m1 * Vector2f(width, radius));
			canvas_element = shape;
		}
		else {
			TS_ASSERT(0 && "ControlFlow::create_socket(): unknown shape");
		}
		
		// element parameters
		canvas_element.setColor(type.color);
		
		return canvas_element;
	}
	
	ControlElement *ControlFlow::create_socket(Control *parent, const Type &type) {
		
		// create element
		Canvas canvas = getCanvas();
		ControlRoot root = getRoot();
		CanvasElement canvas_element = create_socket(canvas, type);
		ControlElement *element = new ControlElement(parent, canvas_element);
		element->setInputMargin(root.getPanelRadius(), getSpacing().y * 0.5f);
		element->setAlign(AlignCenter);
		return element;
	}
	
	void ControlFlow::create_rect(CanvasShape &shape, const Vector2f &p0, const Vector2f &p1, const Vector2f &p2, const Vector2f &p3) {
		shape.addPosition(p0); shape.addPosition(p0); shape.addPosition(p1);
		shape.addPosition(p1); shape.addPosition(p1); shape.addPosition(p2);
		shape.addPosition(p2); shape.addPosition(p2); shape.addPosition(p3);
		shape.addPosition(p3); shape.addPosition(p3); shape.addPosition(p0);
		shape.addPosition(p0); shape.addPosition(p0); shape.addPosition(p0);
	}
	
	/*
	 */
	ControlElement *ControlFlow::create_strip(const Type &type) {
		
		// create strip
		Canvas canvas = getCanvas();
		CanvasStrip strip = CanvasStrip(canvas);
		strip.setWidth(type.connection_width);
		strip.setColor(type.connection_color);
		strip.setStrokeStyle(type.connection_style);
		
		// create element
		ControlElement *element = new ControlElement(&flow_panel, strip);
		for(uint32_t i = 0; i < NumStates; i++) {
			element->setStateColor((State)i, Color::white);
		}
		element->setAlign(AlignOverlap);
		return element;
	}
	
	void ControlFlow::create_strip(ControlElement *element, const Vector2f &p0, const Vector2f &p3, bool clear) {
		CanvasStrip strip = CanvasStrip(element->getElement());
		float32_t radius = min(getRadius() * 16.0f, length(p3 - p0) * 0.5f);
		Vector2f p1 = Vector2f(p0.x + radius, p0.y);
		Vector2f p2 = Vector2f(p3.x - radius, p3.y);
		if(clear) strip.clearPositions();
		strip.createCubic(p0, p1, p2, p3, 0.1f);
	}
	
	void ControlFlow::update_strip(ControlElement *element, const Type &type) {
		CanvasStrip strip = CanvasStrip(element->getElement());
		strip.setWidth(type.connection_width);
		strip.setStrokeStyle(type.connection_style);
		element->setColor(type.connection_color);
	}
	
	/*
	 */
	void ControlFlow::clear_spatial() {
		spatial_indices.clear();
		spatial_nodes.clear();
	}
	
	void ControlFlow::create_input_spatial(uint32_t node_index, uint32_t input_index) {
		
		// check spatial tree
		if(spatial_nodes) return;
		
		// create output indices
		const Type &input_type = get_node_input_type(node_index, input_index);
		const TypeMask &input_mask = get_node_input_mask(node_index, input_index);
		for(const NodePtr &node : nodes) {
			if(node->index == Maxu32) continue;
			for(const NodeOutput &output : node->outputs) {
				const Type &output_type = types[output.type];
				const TypeMask &output_mask = protos[node->proto].outputs[output.index].mask;
				if(!is_compatible_types(output_type, input_type, output_mask, input_mask)) continue;
				if(isInputConnected(node_index, input_index, node->index, output.index)) continue;
				if(!node->is_expanded && !output.connections) continue;
				NodeIndex &node_index = spatial_indices.append();
				node_index.node = node->index;
				node_index.index = output.index;
			}
		}
		
		// create spatial tree
		spatial_nodes.resize(max(spatial_indices.size() * 2, 4u));
		for(uint32_t i = 0; i < spatial_indices.size(); i++) {
			const NodeIndex &node_index = spatial_indices[i];
			Spatial::Node2f &spatial_node = spatial_nodes[spatial_indices.size() + i];
			Vector2f position = getOutputSocket(node_index.node, node_index.index)->getOffset().xy;
			spatial_node.bound.set(position - getRadius(), position + getRadius());
		}
		Spatial::create<float32_t>(spatial_nodes.get(), spatial_indices.size());
	}
	
	void ControlFlow::create_output_spatial(uint32_t node_index, uint32_t output_index) {
		
		// check spatial tree
		if(spatial_nodes) return;
		
		// create input indices
		const Type &output_type = get_node_output_type(node_index, output_index);
		const TypeMask &output_mask = get_node_output_mask(node_index, output_index);
		for(const NodePtr &node : nodes) {
			if(node->index == Maxu32) continue;
			for(const NodeInput &input : node->inputs) {
				const Type &input_type = types[input.type];
				const TypeMask &input_mask = protos[node->proto].inputs[input.index].mask;
				if(!is_compatible_types(output_type, input_type, output_mask, input_mask)) continue;
				if(isOutputConnected(node_index, output_index, node->index, input.index)) continue;
				if(!node->is_expanded && !input.connections) continue;
				NodeIndex &node_index = spatial_indices.append();
				node_index.node = node->index;
				node_index.index = input.index;
			}
		}
		
		// create spatial tree
		spatial_nodes.resize(max(spatial_indices.size() * 2, 4u));
		for(uint32_t i = 0; i < spatial_indices.size(); i++) {
			const NodeIndex &node_index = spatial_indices[i];
			Spatial::Node2f &spatial_node = spatial_nodes[spatial_indices.size() + i];
			Vector2f position = getInputSocket(node_index.node, node_index.index)->getOffset().xy;
			spatial_node.bound.set(position - getRadius(), position + getRadius());
		}
		Spatial::create<float32_t>(spatial_nodes.get(), spatial_indices.size());
	}
	
	/*
	 */
	bool ControlFlow::expand_nodes(const Array<uint32_t> &indices) {
		bool ret = false;
		for(uint32_t index : indices) {
			NodePtr &node = nodes[index];
			if(node->index == Maxu32) continue;
			node->is_expanded = !node->is_expanded;
			node->node_grid.setEnabled(node->is_expanded);
			if(node->node_grid.getNumChildren()) ret = true;
			const Proto &proto = protos[node->proto];
			for(NodeInput &input : node->inputs) {
				uint32_t index = input.index * 2;
				bool is_enabled = (input.connections || node->is_expanded);
				node->input_grid.getChild(index + 0).setEnabled(is_enabled);
				node->input_grid.getChild(index + 1).setEnabled(is_enabled);
				if(proto.inputs[input.index].is_separator) node->input_grid.setRowSpacing(input.index, node->is_expanded ? spacing.y * 2.0f : 0.0f);
				ret = true;
			}
			for(uint32_t i = node->inputs.size() * 2; i < node->input_grid.getNumChildren(); i++) {
				node->input_grid.getChild(i).setEnabled(node->is_expanded);
				ret = true;
			}
			for(NodeOutput &output : node->outputs) {
				uint32_t index = output.index * 2;
				bool is_enabled = (output.connections || node->is_expanded);
				node->output_grid.getChild(index + 0).setEnabled(is_enabled);
				node->output_grid.getChild(index + 1).setEnabled(is_enabled);
				if(proto.outputs[output.index].is_separator) node->output_grid.setRowSpacing(output.index, node->is_expanded ? spacing.y * 2.0f : 0.0f);
				ret = true;
			}
			for(uint32_t i = node->outputs.size() * 2; i < node->output_grid.getNumChildren(); i++) {
				node->output_grid.getChild(i).setEnabled(node->is_expanded);
				ret = true;
			}
			node->dialog.setSize(0.0f, 0.0f);
			update_nodes.append(node->index);
		}
		return ret;
	}
	
	/*
	 */
	Vector2f ControlFlow::get_nodes_center() const {
		BoundRectf nodes_rect;
		for(const NodePtr &node : nodes) {
			if(node->index == Maxu32) continue;
			Vector2f hsize = Vector2f(128.0f);
			if(node->dialog) {
				Rect rect = node->dialog.getRect();
				if(rect) hsize = max(hsize, rect.getSize() * 0.5f);
			}
			nodes_rect.expand(node->position - hsize);
			nodes_rect.expand(node->position + hsize);
		}
		return floor(nodes_rect.getCenter() + 0.5f);
	}
	
	/*****************************************************************************\
	 *
	 * ControlFlow Callbacks
	 *
	\*****************************************************************************/
	
	/*
	 */
	void ControlFlow::flow_pressed_callback(ControlRect rect, float32_t x, float32_t y, ControlFlow *self) {
		
		// create region rect
		ControlRoot root = rect.getRoot();
		ControlRect &region_rect = self->region_rect;
		if(root.getKeyboardKey(KeyCtrl) || region_rect.isEnabled()) {
			ControlRoot root = rect.getRoot();
			Vector2f position = root.getMouse() - self->flow_area.getControlsSize() * 0.5f;
			CanvasRect canvas_rect = region_rect.getCanvasRect();
			if(region_rect.isEnabled()) {
				canvas_rect.setEnabled(true);
				canvas_rect.setOrder(canvas_rect.getOrder() + Maxi16);
				region_rect.setSize(abs(position - self->region_position));
				region_rect.setPosition(Vector3f((position + self->region_position) * 0.5f, 0.0f));
			} else {
				region_rect.setEnabled(true);
				canvas_rect.setEnabled(false);
				region_rect.setSize(Vector2f::zero);
				region_rect.setPosition(Vector3f(position, 0.0f));
				self->flow_grid.raiseChild(region_rect);
				self->region_position = position;
				self->mode = ModeClear;
			}
			return;
		}
		
		// disable callback for flow navigation mode
		if(!self->is_flow_pressed) {
			self->flow_position = Vector2f(x, y);
			self->is_flow_pressed = true;
		} else if(self->is_flow_navigation || abs(self->flow_position.x - x) > 1.0f || abs(self->flow_position.y - y) > 1.0f) {
			root.clearCurrentControl();
			self->is_flow_navigation = true;
			return;
		}
		
		// disable callback if nothing is selected
		if(!self->selected_nodes) {
			root.clearCurrentControl();
			self->mode = ModeClear;
		}
	}
	
	void ControlFlow::flow_released_callback(ControlRect rect, float32_t x, float32_t y, ControlFlow *self) {
		
		// clear selected nodes
		self->add_select_action();
		self->selected_nodes.clear();
		self->current_node_index = Maxu32;
		
		// select nodes by region rect
		if(self->region_rect.isEnabled()) {
			Vector2f rect_hsize = self->region_rect.getSize() * 0.5f;
			Vector2f rect_min = self->region_rect.getPosition().xy - rect_hsize;
			Vector2f rect_max = self->region_rect.getPosition().xy + rect_hsize;
			for(const NodePtr &node : self->nodes) {
				if(node->index == Maxu32) continue;
				Vector2f dialog_hsize = node->dialog.getRect().getSize() * 0.5f;
				Vector2f dialog_min = node->position - dialog_hsize;
				Vector2f dialog_max = node->position + dialog_hsize;
				if(rect_min.x > dialog_max.x || rect_max.x < dialog_min.x) continue;
				if(rect_min.y > dialog_max.y || rect_max.y < dialog_min.y) continue;
				self->selected_nodes.append(node->index);
				self->current_node_index = node->index;
			}
			if(self->selected_nodes) {
				ControlRoot root = rect.getRoot();
				root.setCurrentControl(self->nodes[self->current_node_index]->dialog);
				self->mode = ModeNodePressed;
			}
			self->region_rect.setEnabled(false);
		}
	}
	
	/*
	 */
	void ControlFlow::node_updated_callback(ControlDialog dialog, ControlFlow *self, uint32_t node_index) {
		
		// resize dialog
		dialog.setSize(0.0f, 0.0f);
		
		// disable callback
		ControlRoot root = dialog.getRoot();
		if(root.getKeyboardKey(KeyCtrl)) {
			NodePtr &node = self->nodes[node_index];
			dialog.setPosition(Vector3f(node->position, 0.0f));
			root.clearCurrentControl();
			return;
		}
		
		// clone selected nodes
		if(!self->is_node_clone && root.getKeyboardKey(KeyShift, true)) {
			uint32_t index = self->selected_nodes.findIndex(node_index);
			self->cloneNodes(self->selected_nodes);
			node_index = self->selected_nodes[index];
			root.setCurrentControl(self->nodes[node_index]->dialog);
			self->current_node_index = node_index;
			self->mode = ModeNodePressed;
			self->add_create_action();
			self->is_node_clone = true;
			self->is_node_position = true;
			return;
		}
		
		// position action
		if(!self->is_node_position) {
			self->add_position_action();
			self->is_node_position = true;
		}
		
		// node movement
		NodePtr &node = self->nodes[node_index];
		Vector2f offset = dialog.getPosition().xy - node->position;
		dialog.setPosition(Vector3f(node->position, 0.0f));
		
		// move selected nodes
		Vector2f rect_min = node->position;
		Vector2f rect_max = node->position;
		for(uint32_t index : self->selected_nodes) {
			NodePtr &node = self->nodes[index];
			if(node->index == Maxu32) continue;
			self->setNodePosition(index, node->position + offset);
			Vector2f hsize = node->dialog.getRect().getSize() * 0.5f;
			rect_min = min(rect_min, node->position - hsize);
			rect_max = max(rect_max, node->position + hsize);
		}
		Vector2f rect_size = rect_max - rect_min;
		
		// resize flow
		ControlArea &flow_area = self->flow_area;
		float32_t scale = flow_area.getScale();
		Rect view_rect = flow_area.getViewRect() / scale - flow_area.getControlsOffset() - flow_area.getControlsSize() * 0.5f;
		Vector2f mouse_position = dialog.getMousePosition();
		
		// horizontal resize
		if(view_rect.getWidth() > rect_size.x) {
			if(view_rect.left > rect_min.x && offset.x < 0.0f) {
				float64_t value = flow_area.getHorizontalValue() + offset.x * scale;
				dialog.setMousePosition(mouse_position + Vector2f(offset.x, 0.0f));
				if(value < 0.0) self->flow_resize.x -= (float32_t)value - rect_size.x;
				flow_area.setHorizontalValue(max(value, 0.0));
			} else if(view_rect.right < rect_max.x && offset.x > 0.0f) {
				float64_t value = flow_area.getHorizontalValue() + offset.x * scale;
				float64_t max_value = flow_area.getHorizontalRange() - flow_area.getHorizontalFrame();
				dialog.setMousePosition(mouse_position + Vector2f(offset.x, 0.0f));
				if(value > max_value) self->flow_resize.x += (float32_t)(value - max_value) + rect_size.x;
				flow_area.setHorizontalValue(min(value, max_value));
			}
		}
		
		// vertical resize
		if(view_rect.getHeight() > rect_size.y) {
			if(view_rect.bottom > rect_min.y && offset.y < 0.0f) {
				float64_t value = flow_area.getVerticalValue() + offset.y * scale;
				dialog.setMousePosition(mouse_position + Vector2f(0.0f, offset.y));
				if(value < 0.0) self->flow_resize.y -= (float32_t)value - rect_size.y;
				flow_area.setVerticalValue(max(value, 0.0));
			} else if(view_rect.top < rect_max.y && offset.y > 0.0f) {
				float64_t value = flow_area.getVerticalValue() + offset.y * scale;
				float64_t max_value = flow_area.getVerticalRange() - flow_area.getVerticalFrame();
				dialog.setMousePosition(mouse_position + Vector2f(0.0f, offset.y));
				if(value > max_value) self->flow_resize.y += (float32_t)(value - max_value) + rect_size.y;
				flow_area.setVerticalValue(min(value, max_value));
			}
		}
	}
	
	void ControlFlow::node_pressed_callback(ControlRect rect, float32_t x, float32_t y, ControlFlow *self, uint32_t node_index) {
		
		// multi-selection
		ControlRoot root = rect.getRoot();
		if(root.getKeyboardKey(KeyCtrl)) {
			self->mode = ModeNodePressed;
			self->current_node_index = node_index;
			if(!self->selected_nodes.find(node_index)) {
				self->add_select_action();
				self->selected_nodes.append(node_index);
			}
		}
		
		// new node selection
		if(self->mode != ModeNodePressed || !self->selected_nodes.find(node_index)) {
			self->add_select_action();
			self->mode = ModeNodePressed;
			self->current_node_index = node_index;
			self->selected_nodes.copy({ node_index });
		}
	}
	
	void ControlFlow::node_released_callback(ControlRect rect, float32_t x, float32_t y, ControlFlow *self, uint32_t node_index) {
		self->is_node_clone = false;
		self->is_node_position = false;
	}
	
	void ControlFlow::node_clicked2_callback(ControlRect rect, ControlFlow *self, uint32_t node_index) {
		if(self->expand_nodes(self->selected_nodes)) self->add_expand_action();
	}
	
	/*
	 */
	void ControlFlow::input_pressed_callback(ControlElement *element, float32_t x, float32_t y, ControlFlow *self, uint32_t node, uint32_t input) {
		self->mode = ModeInputPressed;
		self->current_node_index = node;
		self->current_input_index = input;
		self->current_output_index = Maxu32;
		self->mouse_position = element->getOffset().xy + Vector2f(x, y);
		self->create_input_spatial(node, input);
	}
	
	void ControlFlow::input_released_callback(ControlElement *element, float32_t x, float32_t y, ControlFlow *self, uint32_t node, uint32_t input) {
		self->mode = ModeInputReleased;
		self->current_node_index = node;
		self->current_input_index = input;
	}
	
	void ControlFlow::input_clicked2_callback(ControlElement *element, ControlFlow *self, uint32_t node, uint32_t input) {
		self->add_connect_action(Maxu32, Maxu32, node, input);
		self->removeInputConnection(node, input);
	}
	
	/*
	 */
	void ControlFlow::output_pressed_callback(ControlElement *element, float32_t x, float32_t y, ControlFlow *self, uint32_t node, uint32_t output) {
		self->mode = ModeOutputPressed;
		self->current_node_index = node;
		self->current_input_index = Maxu32;
		self->current_output_index = output;
		self->mouse_position = element->getOffset().xy + Vector2f(x, y);
		self->create_output_spatial(node, output);
	}
	
	void ControlFlow::output_released_callback(ControlElement *element, float32_t x, float32_t y, ControlFlow *self, uint32_t node, uint32_t output) {
		self->mode = ModeOutputReleased;
		self->current_node_index = node;
		self->current_output_index = output;
	}
	
	void ControlFlow::output_clicked2_callback(ControlElement *element, ControlFlow *self, uint32_t node, uint32_t output) {
		self->add_connect_action(node, output, Maxu32, Maxu32);
		self->removeOutputConnection(node, output);
	}
	
	/*
	 */
	void ControlFlow::proto_changed_callback(ControlEdit edit, ControlFlow *self) {
		uint32_t num_items = 0;
		String name = self->proto_edit.getText().lower();
		for(const Proto &proto : self->protos) {
			if(proto.item == Maxu32) continue;
			bool is_hidden = (name && !proto.match.contains(name.get()) && !proto.match.match(name.get()));
			self->proto_tree.setItemHidden(proto.item, is_hidden);
			if(!is_hidden) num_items++;
		}
		if(num_items == 0 && self->proto_edit.getText()) {
			String text = self->proto_edit.getText();
			self->proto_edit.setText(text.removeBack());
			proto_changed_callback(edit, self);
			edit.setCurrentIndex(edit.getNumCodes());
		}
	}
	
	/*
	 */
	bool ControlFlow::proto_dragged_callback(ControlTree tree, uint32_t item, ControlFlow *self) {
		self->dragged_tree_item = item;
		return true;
	}
	
	void ControlFlow::proto_dropped_callback(ControlTree tree, uint32_t item, ControlFlow *self) {
		
		// check mouse
		Rect rect = self->proto_dialog.getRect() + self->proto_dialog.getOffset().xy;
		if(rect.inside(tree.getRoot().getMouse())) {
			self->dragged_tree_item = Maxu32;
			return;
		}
		
		// find proto
		for(const Proto &proto : self->protos) {
			if(proto.item == self->dragged_tree_item) {
				ControlRoot root = tree.getRoot();
				Vector2f position = root.getMouse();
				if(self->flow_area.getViewRect().inside(position)) {
					uint32_t node = self->addNode(proto.index, self->get_mouse_position(root), proto.value, proto.state);
					if(self->nodes[node]->create_func) self->nodes[node]->create_func(self, node);
					self->mode = ModeNodePressed;
					self->current_node_index = node;
					self->selected_nodes.copy({ node });
					self->add_create_action();
					root.setCurrentControl(self->nodes[node]->dialog);
					self->proto_edit.setText(nullptr);
					proto_changed_callback(self->proto_edit, self);
				}
				break;
			}
		}
		self->dragged_tree_item = Maxu32;
	}
	
	/*
	 */
	void ControlFlow::input_returned_callback(ControlEdit edit, ControlFlow *self, uint32_t node, uint32_t index) {
		if(edit.getEditMode() == ControlEdit::EditModeNumber) {
			float64_t value = edit.getText().tof64();
			edit.setText(String::fromf64(value, 4, true, abs(value) < 1e-12 || abs(value) > 1e12));
		}
		if(self->getInputValue(node, index) != edit.getText()) {
			self->setInputValue(node, index, edit.getText(), true);
			self->is_changed = true;
		}
		edit.setSelection();
	}
	
	/*
	 */
	void ControlFlow::remove_clicked_callback(ControlButton button, ControlFlow *self) {
		self->add_remove_action();
		for(uint32_t index : self->selected_nodes) {
			if(self->isNodeStatic(index)) continue;
			self->removeNode(index);
		}
		self->current_node_index = Maxu32;
		self->selected_nodes.clear();
		self->mode = ModeClear;
	}
	
	/*
	 */
	uint32_t ControlFlow::get_output_proto(uint32_t input_node, uint32_t input_index, uint32_t &output_index) const {
		return Maxu32;
	}
	
	void ControlFlow::update_output_node(uint32_t input_node, uint32_t input_index, uint32_t output_node, uint32_t output_index) {
		
	}
	
	/*****************************************************************************\
	 *
	 * ControlFlow Unredo
	 *
	\*****************************************************************************/
	
	/*
	 */
	void ControlFlow::add_position_action() {
		Action *action = new Action(ActionPosition);
		action->indices = selected_nodes;
		for(uint32_t node : selected_nodes) {
			action->positions.append(nodes[node]->position);
		}
		add_action(action);
	}
	
	void ControlFlow::add_select_action() {
		Action *action = new Action(ActionSelect);
		action->indices = selected_nodes;
		add_action(action);
	}
	
	void ControlFlow::add_expand_action() {
		Action *action = new Action(ActionExpand);
		action->indices = selected_nodes;
		add_action(action);
	}
	
	void ControlFlow::add_create_action() {
		Action *action = new Action(ActionCreate);
		for(uint32_t index : selected_nodes) {
			NodePtr &node = nodes[index];
			if(node->is_static) continue;
			if(node->index == Maxu32) continue;
			add_indices(action->create_indices, node);
			action->indices.append(index);
		}
		add_action(action);
	}
	
	void ControlFlow::add_remove_action() {
		Action *action = new Action(ActionRemove);
		for(uint32_t index : selected_nodes) {
			NodePtr &node = nodes[index];
			if(node->is_static) continue;
			if(node->index == Maxu32) continue;
			if(node->remove_func) node->remove_func(this, index);
			add_indices(action->remove_indices, node);
			add_node(action, node);
		}
		action->indices.swap(selected_nodes);
		add_action(action);
	}
	
	void ControlFlow::add_connect_action(uint32_t node, uint32_t output, uint32_t input_node, uint32_t input_index) {
		Action *action = new Action(ActionConnect);
		if(node == Maxu32 || (input_node != Maxu32 && !protos[getNodeProto(input_node)].inputs[input_index].is_multi)) {
			for(const InputConnection &input_connection : nodes[input_node]->inputs[input_index].connections) {
				for(const OutputConnection &output_connection : nodes[input_connection.node]->outputs[input_connection.output].connections) {
					if(output_connection.node == input_node && output_connection.input == input_index) {
						action->remove_indices.append(Vector4u(input_connection.node, input_connection.output, input_node, input_index));
					}
				}
			}
		}
		if(input_node == Maxu32 || (node != Maxu32 && !protos[getNodeProto(node)].outputs[output].is_multi)) {
			for(const OutputConnection &output_connection : nodes[node]->outputs[output].connections) {
				for(const InputConnection &input_connection : nodes[output_connection.node]->inputs[output_connection.input].connections) {
					if(input_connection.node == node && input_connection.output == output) {
						action->remove_indices.append(Vector4u(node, output, output_connection.node, output_connection.input));
					}
				}
			}
		}
		if(node != Maxu32 && input_node != Maxu32) {
			action->create_indices.append(Vector4u(node, output, input_node, input_index));
		}
		if(action->create_indices || action->remove_indices) {
			action->indices.swap(selected_nodes);
			add_action(action);
		}
		else delete action;
	}
	
	/*
	 */
	void ControlFlow::add_action(Action *action) {
		undo_actions.append(makeAutoPtr(action));
		for(auto &action : redo_actions) {
			for(Node &node : action->nodes) {
				for(NodeInput &input : node.inputs) {
					if(input.socket) removed_elements.append(input.socket.release());
				}
				for(NodeOutput &output : node.outputs) {
					if(output.socket) removed_elements.append(output.socket.release());
				}
				if(node.dialog) {
					flow_grid.removeChild(node.dialog);
					removed_controls.append(node.dialog);
					node.dialog.clearPtr();
				}
			}
		}
		redo_actions.release();
		if(action_func) action_func(this);
	}
	
	/*
	 */
	void ControlFlow::add_indices(Array<Vector4u> &indices, const NodePtr &node) {
		for(const NodeInput &input : node->inputs) {
			for(const InputConnection &connection : input.connections) {
				indices.append(Vector4u(connection.node, connection.output, node->index, input.index));
			}
		}
		for(const NodeOutput &output : node->outputs) {
			for(const OutputConnection &connection : output.connections) {
				indices.append(Vector4u(node->index, output.index, connection.node, connection.input));
			}
		}
	}
	
	void ControlFlow::add_node(Action *action, NodePtr &node) {
		TS_ASSERT(node->index != Maxu32 && "ControlFlow::add_node(): invalid node index");
		clearConnections(node->index);
		action->nodes.append(node.ref());
		node->dialog.setStrokeStyle(node->stroke_style);
		node->dialog.setEnabled(false);
		node->dialog.clearPtr();
		node->create_func.clear();
		node->update_func.clear();
		node->remove_func.clear();
		node->load_func.clear();
		node->save_func.clear();
		node->index = Maxu32;
	}
	
	/*
	 */
	void ControlFlow::swap_action(Action *action) {
		if(action->type == ActionPosition) {
			for(uint32_t i = 0; i < action->indices.size(); i++) {
				uint32_t node = action->indices[i];
				Vector2f position = nodes[node]->position;
				setNodePosition(node, action->positions[i]);
				action->positions[i] = position;
			}
		}
		else if(action->type == ActionSelect) {
			action->indices.swap(selected_nodes);
		}
		else if(action->type == ActionExpand) {
			expand_nodes(action->indices);
		}
		else if(action->type == ActionCreate) {
			for(uint32_t i = 0; i < action->indices.size(); i++) {
				NodePtr &node = nodes[action->indices[i]];
				if(node->remove_func) node->remove_func(this, node->index);
				add_node(action, nodes[action->indices[i]]);
			}
			action->type = ActionRemove;
			action->create_indices.swap(action->remove_indices);
			mode = ModeClear;
		}
		else if(action->type == ActionRemove) {
			for(uint32_t i = 0; i < action->indices.size(); i++) {
				NodePtr &node = nodes[action->indices[i]];
				node.ref() = action->nodes[i];
				node->dialog.setEnabled(true);
				if(node->create_func) node->create_func(this, node->index);
			}
			for(const Vector4u &index : action->remove_indices) {
				addOutputConnection(index.x, index.y, index.z, index.w);
			}
			action->type = ActionCreate;
			action->create_indices.swap(action->remove_indices);
			action->nodes.release();
			prev_selected_nodes.clear();
			selected_nodes = action->indices;
			mode = ModeNodePressed;
		}
		else if(action->type == ActionConnect) {
			for(const Vector4u &index : action->create_indices) {
				removeOutputConnection(index.x, index.y, index.z, index.w);
			}
			for(const Vector4u &index : action->remove_indices) {
				addOutputConnection(index.x, index.y, index.z, index.w);
			}
			action->indices.swap(selected_nodes);
			action->create_indices.swap(action->remove_indices);
		}
		else if(action->type == ActionValue) {
			NodePtr &node = nodes[action->indices[0]];
			swap(action->data, node->value);
			if(node->create_func) node->create_func(this, action->indices[0]);
			is_changed = true;
		}
		else if(action->type == ActionState) {
			NodePtr &node = nodes[action->indices[0]];
			swap(action->data, node->state);
			if(node->create_func) node->create_func(this, action->indices[0]);
			is_changed = true;
		}
		else if(action->type == ActionInput) {
			NodePtr &node = nodes[action->indices[0]];
			uint32_t index = action->indices[1];
			swap(action->data, node->inputs[index].value);
			if(node->create_func) node->create_func(this, action->indices[0]);
			is_changed = true;
		}
		else if(action->type == ActionOutput) {
			NodePtr &node = nodes[action->indices[0]];
			uint32_t index = action->indices[1];
			swap(action->data, node->outputs[index].value);
			if(node->create_func) node->create_func(this, action->indices[0]);
			is_changed = true;
		}
		else {
			TS_ASSERT(0 && "ControlFlow::swap_action(): unknown action");
		}
	}
	
	/*
	 */
	bool ControlFlow::undo() {
		if(!undo_actions) return false;
		AutoPtr<Action> action = undo_actions.back();
		undo_actions.removeBack();
		swap_action(action.get());
		redo_actions.append(action);
		input_node_index = Maxu32;
		return true;
	}
	
	/*
	 */
	bool ControlFlow::redo() {
		if(!redo_actions) return false;
		AutoPtr<Action> action = redo_actions.back();
		redo_actions.removeBack();
		swap_action(action.get());
		undo_actions.append(action);
		input_node_index = Maxu32;
		return true;
	}
	
	/*****************************************************************************\
	 *
	 * ControlFlow
	 *
	\*****************************************************************************/
	
	/*
	 */
	bool ControlFlow::create(Control *controls_root, Control *base_root) {
		
		TS_ASSERT(!isCreated() && "ControlFlow::create(): is already created");
		
		// parent control
		Control parent = getParent();
		
		// create main grid
		if(!controls_root) controls_root = &parent;
		main_grid = ControlGrid(controls_root);
		main_grid.setAlign(AlignExpand);
		
		// create flow area
		flow_area = ControlArea(&main_grid);
		flow_area.setAbsolute(true);
		flow_area.setScalable(true);
		flow_area.setAlign(AlignExpand);
		flow_area.setFrameAlign(AlignCenter);
		flow_area.setScaleRange(0.5f, 2.0f);
		
		// create flow panel
		flow_panel = ControlPanel(&flow_area);
		flow_panel.setPressedCallback(makeFunction(flow_pressed_callback, ControlRect::null, 0.0f, 0.0f, this));
		flow_panel.setReleasedCallback(makeFunction(flow_released_callback, ControlRect::null, 0.0f, 0.0f, this));
		flow_panel.setColor(Color(0.1f, 1.0f));
		flow_panel.setSize(4096.0f, 2048.0f);
		flow_panel.setAlign(AlignCenter);
		flow_panel.setMargin(0.0f, 0.0f);
		flow_panel.setRadius(0.0f);
		
		// create flow grid
		flow_grid = ControlGrid(&flow_area);
		flow_grid.setAlign(AlignCenter | AlignExpand | AlignOverlap);
		
		// create proto dialog
		proto_dialog = ControlDialog(&main_grid, 1, spacing.x, spacing.y);
		proto_dialog.setAlign(AlignRight | AlignExpandY | AlignOverlap | AlignSpacer);
		proto_dialog.setResizeArea(getRadius() * 0.5f);
		proto_dialog.setSize(192.0f, 192.0f);
		proto_dialog.setRadius(0.0f);
		
		// create proto edit
		proto_edit = ControlEdit(&proto_dialog);
		proto_edit.setChangedCallback(makeFunction(proto_changed_callback, ControlEdit::null, this));
		proto_edit.setAlign(AlignExpandX);
		
		// create proto area
		proto_area = ControlArea(&proto_dialog);
		proto_area.setVerticalEnabled(true, true);
		proto_area.setHorizontalEnabled(true, true);
		proto_area.setAlign(AlignExpand);
		proto_area.setFrameAlign(AlignTop);
		
		// create proto tree
		proto_tree = ControlTree(&proto_area);
		proto_tree.setDraggedCallback(makeFunction(proto_dragged_callback, ControlTree::null, Maxu32, this));
		proto_tree.setDroppedCallback(makeFunction(proto_dropped_callback, ControlTree::null, Maxu32, this));
		proto_tree.setAlign(AlignExpand);
		proto_tree.setExpandedText("");
		proto_tree.setFoldedText("");
		
		// create input grid
		input_grid = ControlGrid(&proto_dialog, 2, spacing.x, spacing.y);
		input_grid.setMargin(0.0f, spacing.y);
		input_grid.setAlign(AlignExpandX);
		
		// create remove button
		remove_button = ControlButton(&proto_dialog, "Remove");
		remove_button.setClickedCallback(makeFunction(remove_clicked_callback, ControlButton::null, this));
		remove_button.setAlign(AlignExpandX);
		
		// create mouse strip
		Canvas canvas = getCanvas();
		mouse_strip = makeAutoPtr(new ControlElement(&flow_panel, CanvasStrip(canvas)));
		mouse_strip->setAlign(AlignOverlap | AlignSpacer);
		
		// create region rect
		region_rect = ControlRect(&flow_grid);
		region_rect.setColor(Color(0.5f, 0.5f));
		region_rect.setStrokeStyle(StrokeStyle(1.0f, Color(1.0f, 0.5f)));
		region_rect.setAlign(AlignCenter | AlignOverlap | AlignSpacer);
		region_rect.setEnabled(false);
		
		// create tooltip
		Control root = getRoot();
		if(base_root == nullptr) base_root = &root;
		tooltip = makeAutoPtr(new ControlTooltip(base_root));
		tooltip->addTooltip(proto_edit, "Filter by name");
		tooltip->addTooltip(remove_button, "Remove selected nodes");
		
		// proto tree tooltip
		tooltip->addTooltip(proto_tree, ControlTooltip::TextCallback([this](Control control, Vector2f *position, float32_t *height) {
			uint32_t item = proto_tree.getFocusedItem();
			if(item == Maxu32) return String::null;
			for(const Proto &proto : protos) {
				if(proto.item != item) continue;
				return getProtoInfo(proto.index);
			}
			return String::null;
		}));
		
		return true;
	}
	
	/*
	 */
	void ControlFlow::update_enabled(bool enabled) {
		enabled &= isEnabled();
		main_grid.setEnabled(enabled);
		ControlBase::update_enabled(enabled);
	}
	
	/*
	 */
	bool ControlFlow::update_keyboard(ControlRoot &root, uint32_t key, uint32_t code) {
		Rect rect = main_grid.getRect() + main_grid.getOffset().xy;
		if(main_grid.isEnabled() && rect.inside(root.getMouse())) {
			if(selected_nodes && !proto_edit.getNumCodes() && (key == KeyDelete || key == KeyBackspace)) {
				remove_clicked_callback(remove_button, this);
				root.getKeyboardKey(key, true);
			}
			else if(key != ' ' && !root.getKeyboardKey(KeyOption)) {
				proto_edit.setCurrentIndex(proto_edit.getNumCodes());
				return proto_edit.updateKeyboard(root, key, code);
			}
		}
		return false;
	}
	
	/*
	 */
	bool ControlFlow::update(ControlRoot &root, const Rect &region, const Rect &view, uint32_t scale) {
		
		bool ret = false;
		
		// update frame
		frame++;
		
		// update proto tree
		if(update_proto_tree) {
			proto_tree.clearItems();
			Map<String, uint32_t> items;
			for(const Proto &proto : protos) {
				if(!proto.text) continue;
				String text = proto.text;
				if(proto.title) text = proto.title;
				items.append(text, proto.index);
			}
			for(const auto &it : items) {
				const String &text = it.key;
				Proto &proto = protos[it.data];
				proto.match = text.lower();
				if(text) {
					Color color = proto.color;
					float32_t value = max(color.r, color.g, color.b);
					if(value > 0.0f) color /= value;
					color.a = 1.0f;
					proto.item = proto_tree.addItem(text);
					proto_tree.setItemColor(proto.item, color);
				} else {
					proto.item = Maxu32;
				}
			}
			proto_changed_callback(proto_edit, this);
			update_proto_tree = false;
		}
		
		// update flow scale
		if(old_size != flow_panel.getRect().getSize() || old_scale != flow_area.getScale()) {
			for(const NodePtr &node : nodes) {
				if(node->index == Maxu32) continue;
				update_nodes.append(node->index);
			}
			old_size = flow_panel.getRect().getSize();
			old_scale = flow_area.getScale();
			ret = true;
		}
		
		// set input control
		if(main_grid.isEnabled()) {
			Control input_control = root.getInputControl();
			if(main_grid.isChild(input_control, true) && !input_control.isEdit()) {
				root.setInputControl(*this);
			}
		}
		
		// changed callback
		if(is_changed && changed_func) {
			changed_func(this);
			is_changed = false;
			frame++;
		}
		
		// move node output under the mouse pointer
		if(mode == ModeNone && mouse_node_index != Maxu32) {
			if(mouse_node_index < nodes.size()) {
				ControlDialog &dialog = nodes[mouse_node_index]->dialog;
				Vector3f offset = getOutputSocket(mouse_node_index, mouse_output_index)->getOffset() - dialog.getOffset();
				offset.y += dialog.getMargin().bottom * 2.0f - dialog.getRect().getHeight();
				dialog.setPosition(dialog.getPosition() - offset * 0.5f);
				nodes[mouse_node_index]->position -= offset.xy * 0.5f;
				update_nodes.append(mouse_node_index);
			}
			mouse_node_index = Maxu32;
			mouse_output_index = Maxu32;
		}
		
		// update selected nodes style
		for(uint32_t index : prev_selected_nodes) {
			if(selected_nodes.find(index)) continue;
			NodePtr &node = nodes[index];
			if(node->index == Maxu32) continue;
			node->dialog.setStrokeStyle(node->stroke_style);
		}
		for(uint32_t index : selected_nodes) {
			if(prev_selected_nodes.find(index)) continue;
			NodePtr &node = nodes[index];
			if(node->index == Maxu32) continue;
			node->stroke_style = node->dialog.getStrokeStyle();
			node->dialog.setStrokeStyle(getSelectionStyle());
		}
		prev_selected_nodes = selected_nodes;
		
		// update node inputs
		if((mode == ModeNodePressed) && current_node_index < nodes.size()) {
			NodePtr &node = nodes[current_node_index];
			if(input_node_index != current_node_index) {
				input_grid.releaseChildren();
				if(node->index != Maxu32) {
					for(NodeInput &input : node->inputs) {
						if(input.connections.size()) continue;
						ProtoInput &proto_input = protos[node->proto].inputs[input.index];
						if(!proto_input.text) continue;
						if(!proto_input.value) continue;
						ControlText text(&input_grid, proto_input.text);
						text.setAlign(AlignRight | AlignCenterY);
						ControlEdit edit(&input_grid, input.value);
						edit.setAlign(AlignExpandX);
						edit.setEditMode(types[proto_input.type].edit_mode);
						edit.setReturnedCallback(makeFunction(input_returned_callback, ControlEdit::null, this, node->index, input.index));
					}
				}
				input_node_index = current_node_index;
			}
		} else {
			input_grid.releaseChildren();
			input_node_index = Maxu32;
		}
		
		// show remove button
		if((mode == ModeNodePressed) && current_node_index < nodes.size() && !isNodeStatic(current_node_index)) {
			remove_button.setEnabled(true);
		} else {
			remove_button.setEnabled(false);
		}
		
		// resize flow panel
		Rect flow_rect = flow_panel.getRect();
		if(update_nodes && !selected_nodes) {
			Vector2f hsize = flow_rect.getSize() * 0.5f;
			for(uint32_t index : update_nodes) {
				NodePtr &node = nodes[index];
				if(node->index == Maxu32) continue;
				flow_resize = max(flow_resize, floor(abs(node->position) - hsize + 0.5f));
			}
		}
		flow_resize = max(flow_resize, floor(flow_area.getViewRect().getSize() / flow_area.getScale() - flow_rect.getSize() + 0.5f));
		if(flow_resize.x > 0.0f || flow_resize.y > 0.0f) {
			flow_panel.setSize(flow_rect.getSize() + flow_resize * 2.0f);
			for(const NodePtr &node : nodes) {
				if(node->index == Maxu32) continue;
				for(NodeInput &input : node->inputs) {
					input.socket->setOffset(input.socket->getOffset() + Vector3f(flow_resize, 0.0f));
				}
				for(NodeOutput &output : node->outputs) {
					output.socket->setOffset(output.socket->getOffset() + Vector3f(flow_resize, 0.0f));
				}
				update_nodes.append(node->index);
			}
		}
		flow_resize = Vector2f::zero;
		
		// update mode
		if(mode == ModeNodePressed) {
			if(old_mode != mode) proto_changed_callback(proto_edit, this);
		}
		else if(mode == ModeInputPressed) {
			
			// mouse strip parameters
			const Type &type = get_node_input_type(current_node_index, current_input_index);
			CanvasStrip strip = CanvasStrip(mouse_strip->getElement());
			strip.setWidth(type.connection_width);
			strip.setStrokeStyle(type.connection_style);
			mouse_strip->setColor(type.connection_color);
			
			// mouse output position
			current_output_index = Spatial::closestIntersection<float32_t>(mouse_position, spatial_nodes.get());
			if(current_output_index < spatial_indices.size()) {
				const NodeIndex &index = spatial_indices[current_output_index];
				Vector2f output_position = getOutputSocket(index.node, index.index)->getOffset().xy;
				if(index.node != current_node_index && length(output_position - mouse_position) < getThreshold()) {
					create_strip(mouse_strip.get(), output_position, mouse_position);
				} else {
					current_output_index = Maxu32;
				}
			}
			
			// create strip
			Vector2f input_position = getInputSocket(current_node_index, current_input_index)->getOffset().xy;
			create_strip(mouse_strip.get(), mouse_position, input_position, (current_output_index >= spatial_indices.size()));
		}
		else if(mode == ModeOutputPressed) {
			
			// mouse strip parameters
			const Type &type = get_node_output_type(current_node_index, current_output_index);
			CanvasStrip strip = CanvasStrip(mouse_strip->getElement());
			strip.setWidth(type.connection_width);
			strip.setStrokeStyle(type.connection_style);
			mouse_strip->setColor(type.connection_color);
			
			// create strip
			Vector2f output_position = getOutputSocket(current_node_index, current_output_index)->getOffset().xy;
			create_strip(mouse_strip.get(), output_position, mouse_position);
			
			// mouse input position
			current_input_index = Spatial::closestIntersection<float32_t>(mouse_position, spatial_nodes.get());
			if(current_input_index < spatial_indices.size()) {
				const NodeIndex &index = spatial_indices[current_input_index];
				Vector2f input_position = getInputSocket(index.node, index.index)->getOffset().xy;
				if(index.node != current_node_index && length(input_position - mouse_position) < getThreshold()) {
					create_strip(mouse_strip.get(), mouse_position, input_position, false);
				} else {
					current_input_index = Maxu32;
				}
			}
		}
		else if(mode == ModeInputReleased) {
			
			// create input connection
			if(current_output_index < spatial_indices.size()) {
				const NodeIndex &index = spatial_indices[current_output_index];
				add_connect_action(index.node, index.index, current_node_index, current_input_index);
				addOutputConnection(index.node, index.index, current_node_index, current_input_index);
				mode = ModeClear;
			}
			else {
				
				// create output proto node
				if(getNumInputConnections(current_node_index, current_input_index) == 0) {
					Vector2f input_position = getInputSocket(current_node_index, current_input_index)->getOffset().xy;
					if(length(mouse_position - input_position) > getThreshold()) {
						uint32_t output_index = Maxu32;
						uint32_t proto_index = get_output_proto(current_node_index, current_input_index, output_index);
						if(proto_index != Maxu32) {
							if(output_index == Maxu32) {
								if(getNumProtoOutputs(proto_index) == 1) {
									output_index = 0;
								} else {
									uint32_t input_type = getInputType(current_node_index, current_input_index);
									for(uint32_t i = 0; i < getNumProtoOutputs(proto_index); i++) {
										if(getProtoOutputType(proto_index, i) == input_type) {
											output_index = i;
											break;
										}
									}
								}
							}
							if(output_index != Maxu32) {
								const Proto &proto = protos[proto_index];
								uint32_t node = addNode(proto_index, get_mouse_position(root), proto.value, proto.state);
								update_output_node(current_node_index, current_input_index, node, output_index);
								if(nodes[node]->create_func) nodes[node]->create_func(this, node);
								addOutputConnection(node, output_index, current_node_index, current_input_index);
								current_node_index = node;
								selected_nodes.copy({ node });
								add_create_action();
								root.setCurrentControl(nodes[node]->dialog);
								proto_edit.setText(nullptr);
								proto_changed_callback(proto_edit, this);
								current_input_index = Maxu32;
								mouse_node_index = node;
								mouse_output_index = output_index;
							}
						}
					}
				}
				
				// remove input connection
				if(current_input_index != Maxu32 && getNumInputConnections(current_node_index, current_input_index) && !isProtoMultiInput(getNodeProto(current_node_index), current_input_index)) {
					Vector2f input_position = getInputSocket(current_node_index, current_input_index)->getOffset().xy;
					if(length(mouse_position - input_position) > getThreshold()) {
						uint32_t output_node = getInputConnectionNode(current_node_index, current_input_index, 0);
						uint32_t output_index = getInputConnectionOutput(current_node_index, current_input_index, 0);
						add_connect_action(Maxu32, Maxu32, current_node_index, current_input_index);
						removeInputConnection(current_node_index, current_input_index, output_node, output_index);
					}
				}
				
				// create output proto tree
				if(current_input_index != Maxu32) {
					String name = proto_edit.getText().lower();
					const Type &input_type = get_node_input_type(current_node_index, current_input_index);
					const TypeMask &input_mask = get_node_input_mask(current_node_index, current_input_index);
					for(const Proto &proto : protos) {
						bool is_hidden = true;
						if(proto.item == Maxu32) continue;
						for(const ProtoOutput &proto_output : proto.outputs) {
							if(!is_compatible_types(types[proto_output.type], input_type, proto_output.mask, input_mask)) continue;
							is_hidden = false;
							break;
						}
						if(!is_hidden) is_hidden = (name && !proto.match.contains(name.get()) && !proto.match.match(name.get()));
						proto_tree.setItemHidden(proto.item, is_hidden);
					}
				}
				
				mode = ModeClear;
				ret = true;
			}
		}
		else if(mode == ModeOutputReleased) {
			
			// create output connection
			if(current_input_index < spatial_indices.size()) {
				const NodeIndex &index = spatial_indices[current_input_index];
				add_connect_action(current_node_index, current_output_index, index.node, index.index);
				addOutputConnection(current_node_index, current_output_index, index.node, index.index);
				mode = ModeClear;
			}
			// create input proto tree
			else {
				String name = proto_edit.getText().lower();
				const Type &output_type = get_node_output_type(current_node_index, current_output_index);
				const TypeMask &output_mask = get_node_output_mask(current_node_index, current_output_index);
				for(const Proto &proto : protos) {
					bool is_hidden = true;
					if(proto.item == Maxu32) continue;
					for(const ProtoInput &proto_input : proto.inputs) {
						if(!is_compatible_types(output_type, types[proto_input.type], output_mask, proto_input.mask)) continue;
						is_hidden = false;
						break;
					}
					if(!is_hidden) is_hidden = (name && !proto.match.contains(name.get()) && !proto.match.match(name.get()));
					proto_tree.setItemHidden(proto.item, is_hidden);
				}
				mode = ModeClear;
				ret = true;
			}
		}
		// clear mode
		else if(mode == ModeClear) {
			CanvasStrip strip = CanvasStrip(mouse_strip->getElement());
			current_node_index = Maxu32;
			current_input_index = Maxu32;
			current_output_index = Maxu32;
			input_node_index = Maxu32;
			strip.clearPositions();
			clear_spatial();
			mode = ModeNone;
			ret = true;
		}
		old_mode = mode;
		
		// focus on loaded nodes and update all strips
		if(is_loaded) {
			if(is_updated) {
				Vector2f center = get_nodes_center() + loaded_position;
				flow_area.setHorizontalValue(floor(flow_area.getHorizontalRange() - flow_area.getHorizontalFrame()) * 0.5 + center.x);
				flow_area.setVerticalValue(floor(flow_area.getVerticalRange() - flow_area.getVerticalFrame()) * 0.5 + center.y);
				for(const NodePtr &node : nodes) {
					if(node->index == Maxu32) continue;
					prev_update_nodes.append(node->index);
				}
				is_loaded = false;
			}
			ret = true;
		}
		
		// create node strips
		for(uint32_t index : prev_update_nodes) {
			NodePtr &node = nodes[index];
			if(node->frame == frame) continue;
			if(node->index == Maxu32) continue;
			node->frame = frame;
			
			// create node outputs
			for(NodeOutput &node_output : node->outputs) {
				if(node_output.frame == frame) continue;
				node_output.frame = frame;
				
				// update output connections
				ControlElement *output_socket = node_output.socket.get();
				Vector2f output_position = output_socket->getOffset().xy;
				for(OutputConnection &output_connection : node_output.connections) {
					if(output_connection.frame == frame) continue;
					ControlElement *input_socket = getInputSocket(output_connection.node, output_connection.input);
					Vector2f input_position = input_socket->getOffset().xy;
					create_strip(output_connection.strip.get(), output_position, input_position);
					output_connection.frame = frame;
				}
			}
			
			// create node inputs
			for(NodeInput &node_input : node->inputs) {
				if(node_input.frame == frame) continue;
				node_input.frame = frame;
				
				// update input connections
				ControlElement *input_socket = node_input.socket.get();
				Vector2f input_position = input_socket->getOffset().xy;
				for(InputConnection &input_connection : node_input.connections) {
					if(input_connection.frame == frame) continue;
					input_connection.frame = frame;
					
					// find output connection
					NodeOutput &node_output = nodes[input_connection.node]->outputs[input_connection.output];
					for(OutputConnection &output_connection : node_output.connections) {
						if(output_connection.frame == frame) continue;
						if(output_connection.node != node->index) continue;
						if(output_connection.input != node_input.index) continue;
						ControlElement *output_socket = node_output.socket.get();
						Vector2f output_position = output_socket->getOffset().xy;
						create_strip(output_connection.strip.get(), output_position, input_position);
						output_connection.frame = frame;
					}
				}
			}
		}
		
		// clear flow navigation mode
		if((is_flow_pressed || is_flow_navigation) && !root.getMouseButtons()) {
			is_flow_pressed = false;
			is_flow_navigation = false;
		}
		
		// updated flag
		is_updated = (!update_nodes && !prev_update_nodes && !next_update_nodes);
		is_updated &= (!removed_controls && !removed_elements);
		
		// remove controls
		for(Control &control : removed_controls) {
			control.destroyPtr();
		}
		removed_controls.clear();
		
		// remove elements
		Canvas canvas = getCanvas();
		for(ControlElement *element : removed_elements) {
			CanvasElement canvas_element = element->getElement();
			canvas.removeElement(canvas_element);
			flow_panel.removeChild(*element);
			removed_controls.append(*element);
		}
		removed_elements.clear();
		
		// clear update nodes
		ret |= (bool)update_nodes;
		prev_update_nodes = update_nodes;
		update_nodes = next_update_nodes;
		next_update_nodes.clear();
		return ret;
	}
}
