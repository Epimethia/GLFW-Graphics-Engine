#pragma once
#include "Tetronimo.h"
#include "Dependencies/GLM/glm.hpp"

class O_Block : public Tetronimo {
public:
	O_Block() {};
	~O_Block() {};

	virtual void Init();
};

class I_Block : public Tetronimo {
public:
	I_Block() {};
	~I_Block() {};

	virtual void Init();
};

class T_Block : public Tetronimo {
public:
	T_Block() {};
	~T_Block() {};

	virtual void Init();
};

class L_Block : public Tetronimo {
public:
	L_Block() {};
	~L_Block() {};

	virtual void Init();
};

class J_Block : public Tetronimo {
public:
	J_Block() {};
	~J_Block() {};

	virtual void Init();
};

class S_Block : public Tetronimo {
public:
	S_Block() {};
	~S_Block() {};

	virtual void Init();
};

class Z_Block : public Tetronimo {
public:
	Z_Block() {};
	~Z_Block() {};

	virtual void Init();
};