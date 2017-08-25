#ifndef FONT_H
#define	FONT_H

unsigned char const Logo[]=
{
	20,21,					// width,height
    0x00,0x06,0x00,0x60,	// raster data - no padding.
    0x00,0x40,0x2F,0x00,
    0xFC,0x03,0x80,0x1F,
    0x00,0xF8,0x01,0x92,
    0x9F,0xF4,0xFB,0xFD,
    0xFE,0xFF,0xE7,0xFF,
    0x7F,0xFF,0xFF,0xEF,
    0xFF,0x7F,0xFC,0xFF,
    0x83,0xFF,0x1F,0xF0,
    0xFF,0x00,0xFE,0x07,
    0xF0,0xFF,0x00,0x60,
    0x00,0x00,0x06,0x00,
    0x60,0x00,0x00,0x06,
	0x00
};


unsigned char const Font[96][7]=
{
	0xFF,0xFF,0xFF,0x55,0x55,0x55,0x55,	//	32	 
	0xFF,0xA0,0xFF,0x55,0x55,0x55,0x55,	//	33	!
	0xF8,0xFF,0xF8,0x55,0x55,0x55,0x55,	//	34	""
	0xEB,0x80,0xEB,0x80,0xEB,0x55,0x55,	//	35	#
	0xD9,0xB6,0x80,0xB6,0xCD,0x55,0x55,	//	36	$
	0x9C,0xEC,0xF7,0x9B,0x9C,0x55,0x55,	//	37	%
	0xC9,0xB6,0xFF,0xDD,0xAF,0x55,0x55,	//	38	&
	0xFB,0xFC,0xFF,0x55,0x55,0x55,0x55,	//	39	'
	0xE3,0xDD,0xBE,0x55,0x55,0x55,0x55,	//	40	(
	0xBE,0xDD,0xE3,0x55,0x55,0x55,0x55,	//	41	)
	0xEB,0xD5,0xE3,0xD5,0xEB,0x55,0x55,	//	42	*
	0xF7,0xF7,0xC1,0xF7,0xF7,0x55,0x55,	//	43	+
	0x7F,0x9F,0x55,0x55,0x55,0x55,0x55,	//	44	,
	0xF7,0xF7,0xF7,0xF7,0xF7,0x55,0x55,	//	45	-
	0xBF,0x55,0x55,0x55,0x55,0x55,0x55,	//	46	.
	0x9F,0xEF,0xF7,0xFB,0xFC,0x55,0x55,	//	47	/
	0xC1,0xAE,0xB6,0xBA,0xC1,0x55,0x55,	//	48	0
	0xFF,0xBD,0x80,0xBF,0xFF,0x55,0x55,	//	49	1
	0x9D,0xAE,0xB6,0xB6,0xB9,0x55,0x55,	//	50	2
	0xDD,0xBE,0xB6,0xB6,0xC9,0x55,0x55,	//	51	3
	0xE7,0xEB,0xED,0x80,0xEF,0x55,0x55,	//	52	4
	0xD8,0xB6,0xB6,0xB6,0xCE,0x55,0x55,	//	53	5
	0xC3,0xB5,0xB6,0xB6,0xCF,0x55,0x55,	//	54	6
	0xFE,0x8E,0xF6,0xFA,0xFC,0x55,0x55,	//	55	7
	0xC9,0xB6,0xB6,0xB6,0xC9,0x55,0x55,	//	56	8
	0xF9,0xB6,0xB6,0xD6,0xE1,0x55,0x55,	//	57	9
	0xEB,0x55,0x55,0x55,0x55,0x55,0x55,	//	58	:
	0x7F,0x97,0x55,0x55,0x55,0x55,0x55,	//	59	;
	0xF7,0xEB,0xDD,0xBE,0x55,0x55,0x55,	//	60	<
	0xEB,0xEB,0xEB,0xEB,0x55,0x55,0x55,	//	61	=
	0xBE,0xDD,0xEB,0xF7,0x55,0x55,0x55,	//	62	>
	0xFD,0xFE,0xAE,0xF6,0xF9,0x55,0x55,	//	63	?
	0xC1,0xBE,0xA2,0xFF,0xB1,0x55,0x55,	//	64	@
	0x83,0xED,0xEE,0xED,0x83,0x55,0x55,	//	65	A
	0x80,0xB6,0xB6,0xB6,0xC9,0x55,0x55,	//	66	B
	0xC1,0xBE,0xBE,0xBE,0xDD,0x55,0x55,	//	67	C
	0x80,0xBE,0xBE,0xDD,0xE3,0x55,0x55,	//	68	D
	0x80,0xB6,0xB6,0xB6,0xBE,0x55,0x55,	//	69	E
	0x80,0xF6,0xF6,0xF6,0xFE,0x55,0x55,	//	70	F
	0xC1,0xBE,0xB6,0xD6,0x8D,0x55,0x55,	//	71	G
	0x80,0xF7,0xF7,0xF7,0x80,0x55,0x55,	//	72	H
	0xBE,0x80,0xBE,0x55,0x55,0x55,0x55,	//	73	I
	0xDF,0xBF,0xBE,0xC0,0xFE,0x55,0x55,	//	74	J
	0x80,0xF7,0xEB,0xDD,0xBE,0x55,0x55,	//	75	K
	0x80,0xBF,0xBF,0xBF,0x55,0x55,0x55,	//	76	L
	0x80,0xFD,0xF3,0xFD,0x80,0x55,0x55,	//	77	M
	0x80,0xF9,0xF7,0xCF,0x80,0x55,0x55,	//	78	N
	0xC1,0xBE,0xBE,0xBE,0xC1,0x55,0x55,	//	79	O
	0x80,0xF6,0xF6,0xF6,0xF9,0x55,0x55,	//	80	P
	0xC1,0xBE,0xAE,0xDE,0xA1,0x55,0x55,	//	81	Q
	0x80,0xF6,0xE6,0xD6,0xB9,0x55,0x55,	//	82	R
	0xD9,0xB6,0xB6,0xB6,0xCD,0x55,0x55,	//	83	S
	0xFE,0xFE,0x80,0xFE,0xFE,0x55,0x55,	//	84	T
	0xC0,0xBF,0xBF,0xBF,0xC0,0x55,0x55,	//	85	U
	0xF0,0xCF,0xBF,0xCF,0xF0,0x55,0x55,	//	86	V
	0xF0,0xCF,0xBF,0xC7,0xBF,0xCF,0xF0,	//	87	W
	0x9C,0xEB,0xF7,0xEB,0x9C,0x55,0x55,	//	88	X
	0xF8,0xF7,0x8F,0xF7,0xF8,0x55,0x55,	//	89	Y
	0x9E,0xAE,0xB6,0xBA,0xBC,0x55,0x55,	//	90	Z
	0x80,0xBE,0xBE,0x55,0x55,0x55,0x55,	//	91	[
	0xFC,0xFB,0xF7,0xEF,0x9F,0x55,0x55,	//	92	
	0xBE,0xBE,0x80,0x55,0x55,0x55,0x55,	//	93	]
	0xF7,0xFB,0xFD,0xFB,0xF7,0x55,0x55,	//	94	^
	0xBF,0xBF,0xBF,0xBF,0xBF,0x55,0x55,	//	95	_
	0xFC,0xFB,0xFF,0x55,0x55,0x55,0x55,	//	96	`
	0xDF,0xAB,0xAB,0x87,0x55,0x55,0x55,	//	97	a
	0x80,0xD7,0xBB,0xBB,0xC7,0x55,0x55,	//	98	b
	0xC7,0xBB,0xBB,0xD7,0x55,0x55,0x55,	//	99	c
	0xC7,0xBB,0xBB,0xD7,0x80,0x55,0x55,	//	100	d
	0xC7,0xAB,0xAB,0xB7,0x55,0x55,0x55,	//	101	e
	0xF7,0x81,0xF6,0xFD,0x55,0x55,0x55,	//	102	f
	0x67,0x5B,0x5B,0xA7,0x55,0x55,0x55,	//	103	g
	0x80,0xF7,0xFB,0xFB,0x87,0x55,0x55,	//	104	h
	0xC2,0xBF,0x55,0x55,0x55,0x55,0x55,	//	105	i
	0x7F,0x7B,0x82,0x55,0x55,0x55,0x55,	//	106	j
	0x80,0xEF,0xD7,0xBB,0x55,0x55,0x55,	//	107	k
	0xFE,0x80,0xFF,0x55,0x55,0x55,0x55,	//	108	l
	0x83,0xF7,0xFB,0x87,0xFB,0x87,0x55,	//	109	m
	0x83,0xF7,0xFB,0xFB,0x87,0x55,0x55,	//	110	n
	0xC7,0xBB,0xBB,0xC7,0x55,0x55,0x55,	//	111	o
	0x03,0xE7,0xDB,0xDB,0xE7,0x55,0x55,	//	112	p
	0xE7,0xDB,0xDB,0xE7,0x03,0x55,0x55,	//	113	q
	0x83,0xF7,0xFB,0xFB,0xF7,0x55,0x55,	//	114	r
	0xB7,0xAB,0xAB,0xDB,0x55,0x55,0x55,	//	115	s
	0xFB,0xC1,0xBB,0x55,0x55,0x55,0x55,	//	116	t
	0xC3,0xBF,0xBF,0xDF,0x83,0x55,0x55,	//	117	u
	0xE3,0xDF,0xBF,0xDF,0xE3,0x55,0x55,	//	118	v
	0xC3,0xBF,0xCF,0xBF,0xC3,0x55,0x55,	//	119	w
	0xBB,0xD7,0xEF,0xD7,0xBB,0x55,0x55,	//	120	x
	0xE3,0x5F,0x5F,0x83,0x55,0x55,0x55,	//	121	y
	0x9B,0xAB,0xAB,0xB3,0x55,0x55,0x55,	//	122	z
	0xF7,0xC9,0xBE,0x55,0x55,0x55,0x55,	//	123	{
	0xFF,0x80,0xFF,0x55,0x55,0x55,0x55,	//	124	|
	0xBE,0xC9,0xF7,0x55,0x55,0x55,0x55,	//	125	}
	0xFF,0xFF,0x55,0x55,0x55,0x55,0x55,	//	126	~
	0x01,0x7D,0x7D,0x7D,0x01,0x55,0x55,	//	127	
};

#endif