/**
* @file MedicineDAO.h
* @author Andrii Dovbush
* @brief MedicineDAO class declaration
*
* Part of Meal-Medicine Delivery System
* This file contains Medicine Data Access Object class declaration.
*/

#ifndef _MEDICINE_DAO_H_
#define _MEDICINE_DAO_H_

#include "../entities/Medicine.h"
#include <vector>

class MedicineDAO {
public:

	void createMedicine(Medicine medicine);

	std::vector<Medicine> readMedicines();

	Medicine readMedicine(long id);

	void updateMedicine(Medicine medicine);

	void deleteMedicine(Medicine medicine);

	void deleteMedicineById(long id);

	void deleteMedicines();
};

#endif // !_MEDICINE_DAO_H_
