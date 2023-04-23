#pragma once
#include <memory>
#include <iostream>
#include <algorithm>
#include <string>
#include <iterator>
#include <vector>
#include <regex>
#include "UnitBase.h"
#include "Resourses.h"
#include "Landscapes.h"
#include "NtrkObj.h"
#include "Snapshot.h"

struct Field
{
private:
	struct fieldElement
	{
		std::shared_ptr<UnitBase> unit;
		std::shared_ptr<NtrlObjNameExpansion> ntrl;

		std::vector<char> name;
		LandscapeTypes type = LandscapeTypes::ground;
		LandscapeInfo effect;
	};
	using FldType = std::shared_ptr<std::shared_ptr<fieldElement[]>[]>;	
	using UnitPtr = std::shared_ptr<UnitBase>;
	void deleteData(Field& f) const;

public:
	Field() = default;
	Field(size_t new_width, size_t new_height);
	Field(Field const& other);
	Field(Field&& other);
	Field& operator=(Field const& other);
	Field& operator=(Field&& other);
	std::shared_ptr<fieldElement[]>& operator[](size_t i);
	std::shared_ptr<fieldElement[]> operator[](size_t i) const;
	std::shared_ptr<Snapshot> save();
	bool load(std::shared_ptr<Snapshot> data);

	void addUnit(std::shared_ptr<UnitBase> unitToAdd, Point p);
	addAndRemoveResult removeUnit(Point p);
	moveResult moveUnit(Point from, Point to);
	
	bool empty() const;
	size_t getHeight() const;
	size_t getWidth() const;

	~Field() = default;

	void swap(Field& other);
	friend void operator<<(std::ostream& out, Field& f);

	struct iterator : std::iterator<std::bidirectional_iterator_tag, fieldElement>
	{
		iterator() = default;
		iterator(FldType& fld, size_t width, size_t height, char c);

		iterator& operator++();
		iterator operator++(int);
		iterator& operator--();
		iterator operator--(int);

		fieldElement& operator*();
		fieldElement* operator->();

		bool operator!=(iterator const& it) const;

	private:
		size_t width = 0;
		size_t height = 0;
		size_t strNumber = 0;
		size_t strIndex = 0;
		FldType* fldPtr;
	};

	iterator begin()
	{
		return iterator(fld, width, height, 'b');
	}
	iterator end()
	{
		return iterator(fld, width, height, 'e');
	}

private:
	size_t width = 0;
	size_t height = 0;
	FldType fld;
};

