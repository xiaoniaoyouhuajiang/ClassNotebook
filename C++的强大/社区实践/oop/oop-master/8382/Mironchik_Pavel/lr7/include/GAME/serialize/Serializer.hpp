#pragma once

#include <istream>

#include <GAME/serialize/ObjectInfo.hpp>

using std::istream;
using std::ostream;

class InObjectsTable;
class OutObjectsTable;

class Serializer {
private:
	static void writeObjectInfo(ostream& os, ObjectInfo* info);
	static void readObjectInfo(istream& is, ObjectInfo* info);

	friend class InObjectsTable;
	friend class OutObjectsTable;

public:
	static const int CONTROL_POINT = 0x12345678;

	static void writeInt(ostream& os, const int* i);
	static void readInt(istream& is, const int* i);

	static void writeFloat(ostream& os, const float* i);
	static void readFloat(istream& is, const float* i);

	static void writeBool(ostream& os, const bool* i);
	static void readBool(istream& is, const bool* i);

	static void writeDouble(ostream& os, const double* i);
	static void readDouble(istream& is, const double* i);

	static void write(ostream& os, const void* p, size_t count);
	static void read(istream& is, void* p, size_t count);

	static void writeControlPoint(ostream& os);
	static bool checkControlPoint(istream& is);

	static void writeControlPoint(ostream& os, int point);
	static bool checkControlPoint(istream& is, int point);
};