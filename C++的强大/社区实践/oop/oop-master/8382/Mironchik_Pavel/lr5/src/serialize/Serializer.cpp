#include <cassert>
#include <string>

#include <GAME/serialize/Serializer.hpp>
#include <GAME/log/Log.hpp>

int write_bytes = 0;
int read_bytes = 0;

void Serializer::writeInt(ostream& os, const int* i) {
	write(os, (void*)i, sizeof(int));
}

void Serializer::readInt(istream& is, const int* i) {
	read(is, (void*)i, sizeof(int));
}

void Serializer::writeFloat(ostream& os, const float* i) {
	write(os, (void*)i, sizeof(float));
}

void Serializer::readFloat(istream& is, const float* i) {
	read(is, (void*)i, sizeof(float));
}

void Serializer::writeBool(ostream& os, const bool* i) {
	write(os, (void*)i, sizeof(bool));
}

void Serializer::readBool(istream& is, const bool* i) {
	read(is, (void*)i, sizeof(bool));
}

void Serializer::writeDouble(ostream& os, const double* i) {
	write(os, (void*)i, sizeof(double));
}

void Serializer::readDouble(istream& is, const double* i) {
	read(is, (void*)i, sizeof(double));
}

void Serializer::writeObjectInfo(ostream& os, ObjectInfo* info) {
	writeControlPoint(os);
	write(os, &(info->object), sizeof(void*));
	write(os, &(info->needWrite), sizeof(bool));
}

void Serializer::readObjectInfo(istream& is, ObjectInfo* info) {
	assert(checkControlPoint(is));
	read(is, &(info->object), sizeof(void*));
	read(is, &(info->needWrite), sizeof(bool));
}

void Serializer::write(ostream& os, const void* p, size_t count) {
	os.write((const char*) p, count);
	write_bytes += count;
}

void Serializer::read(istream& is, void* p, size_t count) {
	is.read((char*)p, count);
	read_bytes += count;
}

void Serializer::writeControlPoint(ostream& os) {
	writeControlPoint(os, CONTROL_POINT);
}

bool Serializer::checkControlPoint(istream& is) {
	return checkControlPoint(is, CONTROL_POINT);
}

void Serializer::writeControlPoint(ostream& os, int point) {
	writeInt(os, &point);
}

bool Serializer::checkControlPoint(istream& is, int point) {
	int checkPoint;
	readInt(is, &checkPoint);
	return checkPoint == point;
}