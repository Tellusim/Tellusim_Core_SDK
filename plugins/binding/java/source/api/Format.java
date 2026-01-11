// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

package com.tellusim;
import com.tellusim.*;

/*
 */
public class Format {
	public enum Enum {
		Unknown(0),
		Ri8(1),
		Ru8(2),
		Ri8n(3),
		Ru8n(4),
		RGi8(5),
		RGu8(6),
		RGi8n(7),
		RGu8n(8),
		RGBi8(9),
		RGBu8(10),
		RGBi8n(11),
		RGBu8n(12),
		RGBu8ns(13),
		RGBAi8(14),
		RGBAu8(15),
		RGBAi8n(16),
		RGBAu8n(17),
		RGBAu8ns(18),
		BGRAu8n(19),
		BGRAu8ns(20),
		Ri16(21),
		Ru16(22),
		Ri16n(23),
		Ru16n(24),
		Rf16(25),
		RGi16(26),
		RGu16(27),
		RGi16n(28),
		RGu16n(29),
		RGf16(30),
		RGBi16(31),
		RGBu16(32),
		RGBi16n(33),
		RGBu16n(34),
		RGBf16(35),
		RGBAi16(36),
		RGBAu16(37),
		RGBAi16n(38),
		RGBAu16n(39),
		RGBAf16(40),
		Ri32(41),
		Ru32(42),
		Rf32(43),
		RGi32(44),
		RGu32(45),
		RGf32(46),
		RGBi32(47),
		RGBu32(48),
		RGBf32(49),
		RGBAi32(50),
		RGBAu32(51),
		RGBAf32(52),
		Ri64(53),
		Ru64(54),
		Rf64(55),
		RGi64(56),
		RGu64(57),
		RGf64(58),
		RGBi64(59),
		RGBu64(60),
		RGBf64(61),
		RGBAi64(62),
		RGBAu64(63),
		RGBAf64(64),
		RGBAu4n(65),
		RGBu5Au1n(66),
		Ru5Gu6Bu5n(67),
		RGBu10Au2(68),
		RGBu10Au2n(69),
		RGf11Bf10(70),
		RGBf9Eu5(71),
		RGBf21(72),
		BC1RGBu8n(73),
		BC1RGBu8ns(74),
		BC1RGBAu8n(75),
		BC1RGBAu8ns(76),
		BC2RGBAu8n(77),
		BC2RGBAu8ns(78),
		BC3RGBAu8n(79),
		BC3RGBAu8ns(80),
		BC4Ri8n(81),
		BC4Ru8n(82),
		BC5RGi8n(83),
		BC5RGu8n(84),
		BC6RGBf16s(85),
		BC6RGBf16u(86),
		BC7RGBAu8n(87),
		BC7RGBAu8ns(88),
		EACRi8n(89),
		EACRu8n(90),
		EACRGi8n(91),
		EACRGu8n(92),
		ETC2RGBu8n(93),
		ETC2RGBu8ns(94),
		ETC2RGBAu8n(95),
		ETC2RGBAu8ns(96),
		ETC2RGBu8Au1n(97),
		ETC2RGBu8Au1ns(98),
		ASTC44RGBAu8n(99),
		ASTC44RGBAu8ns(100),
		ASTC44RGBAf16(101),
		ASTC54RGBAu8n(102),
		ASTC54RGBAu8ns(103),
		ASTC54RGBAf16(104),
		ASTC55RGBAu8n(105),
		ASTC55RGBAu8ns(106),
		ASTC55RGBAf16(107),
		ASTC65RGBAu8n(108),
		ASTC65RGBAu8ns(109),
		ASTC65RGBAf16(110),
		ASTC66RGBAu8n(111),
		ASTC66RGBAu8ns(112),
		ASTC66RGBAf16(113),
		ASTC85RGBAu8n(114),
		ASTC85RGBAu8ns(115),
		ASTC85RGBAf16(116),
		ASTC86RGBAu8n(117),
		ASTC86RGBAu8ns(118),
		ASTC86RGBAf16(119),
		ASTC88RGBAu8n(120),
		ASTC88RGBAu8ns(121),
		ASTC88RGBAf16(122),
		Du16(123),
		Du16Su8(124),
		Du24(125),
		Du24Su8(126),
		Df32(127),
		Df32Su8(128),
		NumFormats(129);
		Enum(int value) { this.value = value; }
		public int value;
	}
	public static final Enum Unknown = Enum.Unknown;
	public static final Enum Ri8 = Enum.Ri8;
	public static final Enum Ru8 = Enum.Ru8;
	public static final Enum Ri8n = Enum.Ri8n;
	public static final Enum Ru8n = Enum.Ru8n;
	public static final Enum RGi8 = Enum.RGi8;
	public static final Enum RGu8 = Enum.RGu8;
	public static final Enum RGi8n = Enum.RGi8n;
	public static final Enum RGu8n = Enum.RGu8n;
	public static final Enum RGBi8 = Enum.RGBi8;
	public static final Enum RGBu8 = Enum.RGBu8;
	public static final Enum RGBi8n = Enum.RGBi8n;
	public static final Enum RGBu8n = Enum.RGBu8n;
	public static final Enum RGBu8ns = Enum.RGBu8ns;
	public static final Enum RGBAi8 = Enum.RGBAi8;
	public static final Enum RGBAu8 = Enum.RGBAu8;
	public static final Enum RGBAi8n = Enum.RGBAi8n;
	public static final Enum RGBAu8n = Enum.RGBAu8n;
	public static final Enum RGBAu8ns = Enum.RGBAu8ns;
	public static final Enum BGRAu8n = Enum.BGRAu8n;
	public static final Enum BGRAu8ns = Enum.BGRAu8ns;
	public static final Enum Ri16 = Enum.Ri16;
	public static final Enum Ru16 = Enum.Ru16;
	public static final Enum Ri16n = Enum.Ri16n;
	public static final Enum Ru16n = Enum.Ru16n;
	public static final Enum Rf16 = Enum.Rf16;
	public static final Enum RGi16 = Enum.RGi16;
	public static final Enum RGu16 = Enum.RGu16;
	public static final Enum RGi16n = Enum.RGi16n;
	public static final Enum RGu16n = Enum.RGu16n;
	public static final Enum RGf16 = Enum.RGf16;
	public static final Enum RGBi16 = Enum.RGBi16;
	public static final Enum RGBu16 = Enum.RGBu16;
	public static final Enum RGBi16n = Enum.RGBi16n;
	public static final Enum RGBu16n = Enum.RGBu16n;
	public static final Enum RGBf16 = Enum.RGBf16;
	public static final Enum RGBAi16 = Enum.RGBAi16;
	public static final Enum RGBAu16 = Enum.RGBAu16;
	public static final Enum RGBAi16n = Enum.RGBAi16n;
	public static final Enum RGBAu16n = Enum.RGBAu16n;
	public static final Enum RGBAf16 = Enum.RGBAf16;
	public static final Enum Ri32 = Enum.Ri32;
	public static final Enum Ru32 = Enum.Ru32;
	public static final Enum Rf32 = Enum.Rf32;
	public static final Enum RGi32 = Enum.RGi32;
	public static final Enum RGu32 = Enum.RGu32;
	public static final Enum RGf32 = Enum.RGf32;
	public static final Enum RGBi32 = Enum.RGBi32;
	public static final Enum RGBu32 = Enum.RGBu32;
	public static final Enum RGBf32 = Enum.RGBf32;
	public static final Enum RGBAi32 = Enum.RGBAi32;
	public static final Enum RGBAu32 = Enum.RGBAu32;
	public static final Enum RGBAf32 = Enum.RGBAf32;
	public static final Enum Ri64 = Enum.Ri64;
	public static final Enum Ru64 = Enum.Ru64;
	public static final Enum Rf64 = Enum.Rf64;
	public static final Enum RGi64 = Enum.RGi64;
	public static final Enum RGu64 = Enum.RGu64;
	public static final Enum RGf64 = Enum.RGf64;
	public static final Enum RGBi64 = Enum.RGBi64;
	public static final Enum RGBu64 = Enum.RGBu64;
	public static final Enum RGBf64 = Enum.RGBf64;
	public static final Enum RGBAi64 = Enum.RGBAi64;
	public static final Enum RGBAu64 = Enum.RGBAu64;
	public static final Enum RGBAf64 = Enum.RGBAf64;
	public static final Enum RGBAu4n = Enum.RGBAu4n;
	public static final Enum RGBu5Au1n = Enum.RGBu5Au1n;
	public static final Enum Ru5Gu6Bu5n = Enum.Ru5Gu6Bu5n;
	public static final Enum RGBu10Au2 = Enum.RGBu10Au2;
	public static final Enum RGBu10Au2n = Enum.RGBu10Au2n;
	public static final Enum RGf11Bf10 = Enum.RGf11Bf10;
	public static final Enum RGBf9Eu5 = Enum.RGBf9Eu5;
	public static final Enum RGBf21 = Enum.RGBf21;
	public static final Enum BC1RGBu8n = Enum.BC1RGBu8n;
	public static final Enum BC1RGBu8ns = Enum.BC1RGBu8ns;
	public static final Enum BC1RGBAu8n = Enum.BC1RGBAu8n;
	public static final Enum BC1RGBAu8ns = Enum.BC1RGBAu8ns;
	public static final Enum BC2RGBAu8n = Enum.BC2RGBAu8n;
	public static final Enum BC2RGBAu8ns = Enum.BC2RGBAu8ns;
	public static final Enum BC3RGBAu8n = Enum.BC3RGBAu8n;
	public static final Enum BC3RGBAu8ns = Enum.BC3RGBAu8ns;
	public static final Enum BC4Ri8n = Enum.BC4Ri8n;
	public static final Enum BC4Ru8n = Enum.BC4Ru8n;
	public static final Enum BC5RGi8n = Enum.BC5RGi8n;
	public static final Enum BC5RGu8n = Enum.BC5RGu8n;
	public static final Enum BC6RGBf16s = Enum.BC6RGBf16s;
	public static final Enum BC6RGBf16u = Enum.BC6RGBf16u;
	public static final Enum BC7RGBAu8n = Enum.BC7RGBAu8n;
	public static final Enum BC7RGBAu8ns = Enum.BC7RGBAu8ns;
	public static final Enum EACRi8n = Enum.EACRi8n;
	public static final Enum EACRu8n = Enum.EACRu8n;
	public static final Enum EACRGi8n = Enum.EACRGi8n;
	public static final Enum EACRGu8n = Enum.EACRGu8n;
	public static final Enum ETC2RGBu8n = Enum.ETC2RGBu8n;
	public static final Enum ETC2RGBu8ns = Enum.ETC2RGBu8ns;
	public static final Enum ETC2RGBAu8n = Enum.ETC2RGBAu8n;
	public static final Enum ETC2RGBAu8ns = Enum.ETC2RGBAu8ns;
	public static final Enum ETC2RGBu8Au1n = Enum.ETC2RGBu8Au1n;
	public static final Enum ETC2RGBu8Au1ns = Enum.ETC2RGBu8Au1ns;
	public static final Enum ASTC44RGBAu8n = Enum.ASTC44RGBAu8n;
	public static final Enum ASTC44RGBAu8ns = Enum.ASTC44RGBAu8ns;
	public static final Enum ASTC44RGBAf16 = Enum.ASTC44RGBAf16;
	public static final Enum ASTC54RGBAu8n = Enum.ASTC54RGBAu8n;
	public static final Enum ASTC54RGBAu8ns = Enum.ASTC54RGBAu8ns;
	public static final Enum ASTC54RGBAf16 = Enum.ASTC54RGBAf16;
	public static final Enum ASTC55RGBAu8n = Enum.ASTC55RGBAu8n;
	public static final Enum ASTC55RGBAu8ns = Enum.ASTC55RGBAu8ns;
	public static final Enum ASTC55RGBAf16 = Enum.ASTC55RGBAf16;
	public static final Enum ASTC65RGBAu8n = Enum.ASTC65RGBAu8n;
	public static final Enum ASTC65RGBAu8ns = Enum.ASTC65RGBAu8ns;
	public static final Enum ASTC65RGBAf16 = Enum.ASTC65RGBAf16;
	public static final Enum ASTC66RGBAu8n = Enum.ASTC66RGBAu8n;
	public static final Enum ASTC66RGBAu8ns = Enum.ASTC66RGBAu8ns;
	public static final Enum ASTC66RGBAf16 = Enum.ASTC66RGBAf16;
	public static final Enum ASTC85RGBAu8n = Enum.ASTC85RGBAu8n;
	public static final Enum ASTC85RGBAu8ns = Enum.ASTC85RGBAu8ns;
	public static final Enum ASTC85RGBAf16 = Enum.ASTC85RGBAf16;
	public static final Enum ASTC86RGBAu8n = Enum.ASTC86RGBAu8n;
	public static final Enum ASTC86RGBAu8ns = Enum.ASTC86RGBAu8ns;
	public static final Enum ASTC86RGBAf16 = Enum.ASTC86RGBAf16;
	public static final Enum ASTC88RGBAu8n = Enum.ASTC88RGBAu8n;
	public static final Enum ASTC88RGBAu8ns = Enum.ASTC88RGBAu8ns;
	public static final Enum ASTC88RGBAf16 = Enum.ASTC88RGBAf16;
	public static final Enum Du16 = Enum.Du16;
	public static final Enum Du16Su8 = Enum.Du16Su8;
	public static final Enum Du24 = Enum.Du24;
	public static final Enum Du24Su8 = Enum.Du24Su8;
	public static final Enum Df32 = Enum.Df32;
	public static final Enum Df32Su8 = Enum.Df32Su8;
	public static final Enum NumFormats = Enum.NumFormats;
	public Format(int value) { this.value = value; }
	public Format(Enum e) { this(e.value); }
	public boolean equals(int v) { return (value == v); }
	public boolean equals(Enum e) { return (value == e.value); }
	public int value;
}
