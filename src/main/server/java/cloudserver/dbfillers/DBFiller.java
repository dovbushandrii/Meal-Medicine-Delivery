package cloudserver.dbfillers;

import cloudserver.model.daos.*;
import cloudserver.model.entities.*;
import org.apache.tomcat.util.codec.binary.Base64;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import javax.transaction.Transactional;
import java.io.File;
import java.io.FileInputStream;
import java.nio.file.Path;
import java.util.List;
import java.util.Random;
import java.util.stream.Collectors;

@Component("DBFiller")
public class DBFiller {

    private final int allergenCount = 10;
    private final int clientCount = 10;
    private final int facilityCount = 10;
    private final int mealInFacilityCount = 10;
    private final int medicineInFacilityCount = 10;
    private final int orderCount = 10;
    private String mealImage = "";
    private String medicineImage = "";

    @Autowired
    private AllergenDAO allergenDAO;
    @Autowired
    private ClientDAO clientDAO;
    @Autowired
    private FacilityDAO facilityDAO;
    @Autowired
    private MealDAO mealDAO;
    @Autowired
    private MedicineDAO medicineDAO;
    @Autowired
    private OrderDAO orderDAO;

    private void readMealPhoto() {
        File f =  new File("meal.jpg");
        try{
            mealImage = encodeFileToBase64Binary(f);
        }
        catch(Exception e) {
            e.printStackTrace();
        }

    }

    private void readMedicinePhoto() {
        File f =  new File("pills.jpg");
        try{
            medicineImage = encodeFileToBase64Binary(f);
        }
        catch(Exception e){
            e.printStackTrace();
        }
    }

    private static String encodeFileToBase64Binary(File file) throws Exception{
        FileInputStream fileInputStreamReader = new FileInputStream(file);
        byte[] bytes = new byte[(int)file.length()];
        fileInputStreamReader.read(bytes);
        return new String(Base64.encodeBase64(bytes), "UTF-8");
    }

    public void resetDB() {
        readMealPhoto();
        readMedicinePhoto();
        clearDB();
        fillAllergens();
        fillClients();
        fillMeals();
        fillMedicines();
        fillFacilities();
        fillOrders();
    }

    private void clearDB() {
        orderDAO.delete();
        facilityDAO.delete();
        mealDAO.delete();
        medicineDAO.delete();
        clientDAO.delete();
        allergenDAO.delete();
    }

    private void fillAllergens() {
        for (int i = 0; i < allergenCount; i++) {
            Allergen al = new Allergen();
            al.setName("allergen" + i);
            allergenDAO.create(al);
        }
    }

    private void fillClients() {
        for (int i = 0; i < clientCount; i++) {
            Client client = new Client();
            client.setEmail("client@mail" + i);
            client.setPhoneNumber("420111111111");
            client.setName("clientName" + i);
            client.setSurname("clientSurname" + i);
            int allergCount = (int)(Math.random() * allergenCount);
            List<Allergen> allergens = allergenDAO.read()
                    .stream()
                    .limit(allergCount)
                    .collect(Collectors.toList());
            client.setAllergens(allergens);
            clientDAO.create(client);
        }
    }

    private void fillFacilities() {
        for (int i = 0; i < facilityCount; i++) {
            Facility facility = new Facility();
            facility.setName("facilityName" + i);
            facility.setPhoneNumber("420222222222");
            List<Meal> meals = mealDAO.read();
            List<Medicine> medicines = medicineDAO.read();
            facility.setMealList(meals.subList(i * mealInFacilityCount, (i + 1) * mealInFacilityCount - 1));
            facility.setMedicineList(medicines.subList(i * medicineInFacilityCount, (i + 1) * medicineInFacilityCount - 1));
            facilityDAO.create(facility);
        }
    }

    private void fillMeals() {
        for (int j = 0; j < facilityCount; j++) {
            for (int i = 0; i < mealInFacilityCount; i++) {
                Meal meal = new Meal();
                meal.setDescription("mealDescription" + j + "_" + i);
                meal.setPrice(Math.random() * 1000.0);
                meal.setWeight((int)(Math.random() * 500.0));
                meal.setImage(mealImage);
                mealDAO.create(meal);
            }
        }
    }

    private void fillMedicines() {
        for (int j = 0; j < facilityCount; j++) {
            for (int i = 0; i < medicineInFacilityCount; i++) {
                Medicine medicine = new Medicine();
                medicine.setDescription("medicineDescription" + j + "_" + i);
                medicine.setPrice(Math.random() * 1000.0);
                medicine.setImage(medicineImage);
                medicineDAO.create(medicine);
            }
        }
    }

    private void fillOrders() {

    }


}
