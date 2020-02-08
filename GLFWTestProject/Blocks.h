#pragma once
#include "Tetronimo.h"
#include "Dependencies/GLM/glm.hpp"

class O_Block : public Tetronimo {
public:
	
	O_Block() { m_PerBlockOffset = { TetronimoSpacing, TetronimoSpacing }; };
	~O_Block() {};

	virtual void Init();
};

class I_Block : public Tetronimo {
public:
	I_Block() { m_PerBlockOffset = { 0.0f, 2.0f * TetronimoSpacing }; };
	~I_Block() {};

	virtual void Init();
};

class T_Block : public Tetronimo {
public:
	T_Block() { m_PerBlockOffset = { TetronimoHalfSpacing , TetronimoHalfSpacing }; };
	~T_Block() {};

	virtual void Init();
};

class L_Block : public Tetronimo {
public:
	L_Block() { m_PerBlockOffset = { TetronimoHalfSpacing , TetronimoHalfSpacing }; };
	~L_Block() {};

	virtual void Init();
};

class J_Block : public Tetronimo {
public:
	J_Block() { m_PerBlockOffset = { TetronimoHalfSpacing , TetronimoHalfSpacing }; };
	~J_Block() {};

	virtual void Init();
};

class S_Block : public Tetronimo {
public:
	S_Block() { m_PerBlockOffset = { TetronimoHalfSpacing , TetronimoHalfSpacing }; };
	~S_Block() {};

	virtual void Init();
};

class Z_Block : public Tetronimo {
public:
	Z_Block() { m_PerBlockOffset = { TetronimoHalfSpacing , TetronimoHalfSpacing }; };
	~Z_Block() {};

	virtual void Init();
};