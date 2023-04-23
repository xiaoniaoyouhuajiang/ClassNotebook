#pragma once

class NeutralObject;

class NeutralFactory {
public:
	virtual NeutralObject* createObject(int x, int y) = 0;
	virtual ~NeutralFactory();
};

class PosionFactory : public NeutralFactory {
public:
	NeutralObject* createObject(int x, int y);
};

class KnivesFactory : public NeutralFactory {
public:
	NeutralObject* createObject(int x, int y);
};

class ArrowFactory : public NeutralFactory {
public:
	NeutralObject* createObject(int x, int y);
};

class DoubleFactory : public NeutralFactory {
public:
	NeutralObject* createObject(int x, int y);
};

class PlusFactory : public NeutralFactory {
public:
	NeutralObject* createObject(int x, int y);
};