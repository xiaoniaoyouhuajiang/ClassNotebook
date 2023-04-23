#include "DoctorCreator.h"
#include "Doctor.h"

std::shared_ptr<Unit> DoctorCreator::make_unit() const {
    return std::make_shared<Doctor>();
}