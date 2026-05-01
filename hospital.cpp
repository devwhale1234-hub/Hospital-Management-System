#include <iostream>
#include <string>
#include <fstream>
using namespace std;
//appointnment details class 
class appointmentDetail
{
    string appointmentbyName;
    string appointmentbyId;
    string appointmenttoName;
    string appointmenttoId;
    string appointmentDay;
public:
    appointmentDetail()
    {
        appointmentbyName = " ";
        appointmentbyId = " ";
        appointmenttoName = " ";
        appointmenttoId = " ";
        appointmentDay = " ";
    }
    appointmentDetail(string byname, string byid, string toname, string toid, string day)
    {
        appointmentbyName = byname;
        appointmentbyId = byid;
        appointmenttoName = toname;
        appointmenttoId = toid;
        appointmentDay = day;
    }
    void setappointmentbyName(string name)
    {
        appointmentbyName = name;
    }
    void setappointmentbyId(string id)
    {
        appointmentbyId = id;
    }
    void setappointmenttoName(string name)
    {
        appointmenttoName = name;
    }
    void setappointmenttoId(string id)
    {
        appointmenttoId = id;
    }
    void setappointmentDay(string day)
    {
        appointmentDay = day;
    }
    string getappointmentbyName()
    {
        return appointmentbyName;
    }
    string getappointmentbyId()
    {
        return appointmentbyId;
    }
    string getappointmenttoName()
    {
        return appointmenttoName;
    }
    string getappointmenttoId()
    {
        return  appointmenttoId;
    }
    string getappointmentDay()
    {
        return  appointmentDay;
    }
};
//health record class 
class healthRecords
{
    string symptoms;
    string diagnosis;
public:
    healthRecords()
    {
        symptoms = " ";
        diagnosis = " ";
    }
    healthRecords(string symptom, string diagnose) : symptoms(symptom), diagnosis(diagnose)
    {
    }
    void setSymptoms(string symptom)
    {
        symptoms = symptom;
    }
    void setDiagnosis(string diagnose)
    {
        diagnosis = diagnose;
    }
    string getSymptoms()
    {
        return symptoms;
    }
    string getDiagnosis()
    {
        return diagnosis;
    }
};
//base person class
class common_person
{
    string common_person_id;
    string common_person_name;
    int common_person_age;
public:
    common_person()
    {
        common_person_id = " ";
        common_person_name = " ";
        common_person_age = 0;
    }
    common_person(string id, string name, int age)
    {
        common_person_id = id;
        common_person_name = name;
        common_person_age = age;
    }
    common_person(common_person& p)
    {
        this->common_person_id = p.common_person_id;
        this->common_person_name = p.common_person_name;
        this->common_person_age = p.common_person_age;
    }
    void setcommonpersonID(string id)
    {
        common_person_id = id;
    }
    void setcommonpersonName(string name)
    {
        common_person_name = name;
    }
    void setcommonpersonAge(int age)
    {
        common_person_age = age;
    }
    string getcommonpersonID()
    {
        return common_person_id;
    }
    int getcommonpersonAge()
    {
        return common_person_age;
    }
    string getcommonpersonName()
    {
        return common_person_name;
    }
};
//patient class
class patient : public common_person
{
    string patientType;
    healthRecords record;
public:
    patient()
    {
        patientType = "General";
    }
    patient(string id, string name, int age, string type, string symptom, string diagnose) : common_person(id, name, age), patientType(type), record(symptom, diagnose)
    {

    }
    patient(patient& p)
    {
        this->setcommonpersonID(p.getcommonpersonID());
        this->setcommonpersonName(p.getcommonpersonName());
        this->setcommonpersonAge(p.getcommonpersonAge());
        this->patientType = p.patientType;
        this->record = p.record;
    }
    void setpatientType(string type)
    {
        patientType = type;
    }
    void setSymptoms(string symptom)
    {
        record.setSymptoms(symptom);
    }
    void setDiagnosis(string diagnose)
    {
        record.setDiagnosis(diagnose);
    }
    void setRecord(healthRecords& h)
    {
        record = h;
    }
    healthRecords& getRecord()
    {
        return record;
    }
    string getSymptoms()
    {
        return record.getSymptoms();
    }
    string getDiagnosis()
    {
        return record.getDiagnosis();
    }
    string getpatientType()
    {
        return patientType;
    }
    void display()
    {
        cout << "Patient Information" << endl;
        cout << "Patient name : " << this->getcommonpersonName() << endl;
        cout << "patient id : " << this->getcommonpersonID() << endl;
        cout << "Patient Age : " << this->getcommonpersonAge() << endl;
        cout << "Patient Type : " << patientType << endl;
        cout << "Pateint Health Record " << endl;
        cout << "Patient Symptoms : " << getSymptoms() << endl;
        cout << "Pateitn Diagnosis : " << getDiagnosis() << endl;
    }

};
//admin class 
class admin : public common_person
{
    string checkSuggestion;
    string checkComplain;
};
//doctor class
class doctor : public common_person
{
    string doctorType;
    string doctorStatus;
    int doctorFee;
    int doctorSalary;
    bool appointmentStatus;
    appointmentDetail* appdetailPtr;
public:
    doctor()
    {
        doctorType = "General";
        doctorStatus = "free";
        doctorFee = 0;
        doctorSalary = 0;
        appointmentStatus = false;
        appdetailPtr = NULL;
    }
    doctor(string id, string name, int age, string type, string status, int fee, int salary, bool app_status, appointmentDetail* ap) : common_person(id, name, age), doctorType(type), doctorStatus(status), doctorFee(fee), doctorSalary(salary), appointmentStatus(app_status), appdetailPtr(ap)
    {
    }

    doctor(doctor& d) {
        this->setcommonpersonID(d.getcommonpersonID());
        this->setcommonpersonName(d.getcommonpersonName());
        this->setcommonpersonAge(d.getcommonpersonAge());
        this->doctorType = d.doctorType;
        this->doctorStatus = d.doctorStatus;
        this->doctorFee = d.doctorFee;
        this->doctorSalary = d.doctorSalary;
        this->appointmentStatus = d.appointmentStatus;
        if (d.appdetailPtr != NULL)
        {
            this->appdetailPtr = new appointmentDetail(*d.appdetailPtr);
        }
        else
            this->appdetailPtr = NULL;
    }
    void setdoctorType(string type)
    {
        doctorType = type;
    }
    void setdoctorStatus(string status)
    {
        doctorStatus = status;
    }
    void setappointmentStatus(bool status)
    {
        appointmentStatus = status;
    }
    bool getappointmentStatus()
    {
        return appointmentStatus;
    }

    void setdoctorFee(int fee)
    {
        doctorFee = fee;
    }
    void setdoctorSalary(int Salary)
    {
        doctorSalary = Salary;
    }
    void setappointmentbyName(string name)
    {
        appdetailPtr->setappointmentbyName(name);   // at the place where we have done doctor[i].setstatus("free") then we have to d0
    }                                             // doctor.getappdetailptr()->setappointmentbyName(name) ; 
    void setappointmentbyId(string id)
    {
        appdetailPtr->setappointmentbyId(id);
    }
    void setappointmenttoName(string name)
    {
        appdetailPtr->setappointmenttoName(name);
    }
    void setappointmenttoId(string id)
    {
        appdetailPtr->setappointmenttoId(id);
    }
    void setappointmentDay(string day)
    {
        appdetailPtr->setappointmentDay(day);
    }
    void setappdetailptr(appointmentDetail* ap)
    {
        appdetailPtr = ap;
    }
    appointmentDetail* getappdetailptr()
    {
        return appdetailPtr;    // returns the pointer of the appointment 
    }
    string getappointmentbyName()
    {
        return appdetailPtr->getappointmentbyName();
    }
    string getappointmentbyId()
    {
        return appdetailPtr->getappointmentbyId();
    }
    string getappointmenttoName()
    {
        return appdetailPtr->getappointmenttoName();
    }
    string getappointmenttoId()
    {
        return  appdetailPtr->getappointmenttoId();
    }
    string getappointmentDay()
    {
        return  appdetailPtr->getappointmentDay();
    }
    string getdoctorType()
    {
        return doctorType;
    }
    string getdoctorStatus()
    {
        return doctorStatus;
    }
    int getdoctorFee()
    {
        return doctorFee;
    }
    int getdoctorSalary()
    {
        return doctorSalary;
    }
    ~doctor()
    {
        delete appdetailPtr;
    }
};
//medicine class(Functions and members added as req for pharmacy class)
class medicine
{
    string name;
    string medicineType;
    int medicineQuantity;
    string medicineTime;

public:
    medicine()
    {
        name = " ";
        medicineType = "normal";
        medicineQuantity = 0;
        medicineTime = " ";
    }

    medicine(string n, string type, int quantity, string time)
    {
        name = n;
        medicineType = type;
        medicineQuantity = quantity;
        medicineTime = time;
    }

    medicine(medicine& m)
    {
        this->name = m.name;
        this->medicineType = m.medicineType;
        this->medicineQuantity = m.medicineQuantity;
        this->medicineTime = m.medicineTime;
    }
    string getmedicineName()
    {
        return name;
    }

    string getmedicineType()
    {
        return medicineType;
    }

    string getmedicineTime()
    {
        return medicineTime;
    }

    int getmedicineQuantity()
    {
        return medicineQuantity;
    }

    void setmedicineName(string n)
    {
        name = n;
    }

    void setmedicineType(string type)
    {
        medicineType = type;
    }

    void setmedicineQuantity(int num)
    {
        medicineQuantity = num;
    }

    void setmedicineTime(string time)
    {
        medicineTime = time;
    }
};
// precription class (Functions and members added as req for pharmacy class)
class prescription
{
    doctor* docPtr;
    patient Patient;
    int numberofmedicines;
    medicine* medicinePtr;
public:
    prescription()
    {
        docPtr = NULL;
        numberofmedicines = 0;
        medicinePtr = NULL;
    }
    prescription(doctor* d, patient p, int num)
    {
        docPtr = d;
        Patient = p;
        numberofmedicines = num;
        if (num > 0)
        {
            medicinePtr = new medicine[num];
            fillMedicine(num);
        }
        else
            medicinePtr = NULL;
    }
    void display()
    {
        cout << "Medicine Prescription" << endl;
        if (docPtr != NULL)
        {
            cout << "Doctor name : " << this->docPtr->getcommonpersonName() << endl;
            cout << "Doctor id : " << this->docPtr->getcommonpersonID() << endl;
        }
        else
        {
            cout << "No doctor assigned " << endl;
        }
        cout << "Patient name : " << this->Patient.getcommonpersonName() << endl;
        cout << "Patient id : " << this->Patient.getcommonpersonID() << endl;
        cout << "Patient Age : " << this->Patient.getcommonpersonAge() << endl;
        cout << "Patient Diagnosis : " << this->Patient.getDiagnosis() << endl;
        if (medicinePtr != NULL)
        {
            for (int i = 0; i < numberofmedicines; i++)
            {
                cout << "Medicine : " << i + 1 << endl;
                cout << "Medicine Name : " << medicinePtr[i].getmedicineName() << endl;
                cout << "Medicine Type : " << medicinePtr[i].getmedicineType() << endl;
                cout << "Medicine Quantity : " << medicinePtr[i].getmedicineQuantity() << endl;
                cout << "Medicine Time : " << medicinePtr[i].getmedicineTime() << endl;
            }

        }
        else
            cout << "No Medicine assigned " << endl;

    }
    void fillMedicine(int num)
    {
        int bufferint;
        string bufferstring;
        for (int i = 0; i < num; i++)
        {
            cout << "Enter medicine : " << i << endl;
            cout << "Enter medicine Name: ";
            cin >> bufferstring;
            medicinePtr[i].setmedicineName(bufferstring);
            cout << "Enter medicine Type : ";
            cin >> bufferstring;
            medicinePtr[i].setmedicineType(bufferstring);
            cout << "Enter medicine quantity : ";
            cin >> bufferint;
            medicinePtr[i].setmedicineQuantity(bufferint);
            cout << "Enter medicine Time: ";
            cin >> bufferstring;
            medicinePtr[i].setmedicineTime(bufferstring);
        }
    }
    int getCount()
    {
        return numberofmedicines;
    }

    medicine getMedicine(int i)
    {
        return medicinePtr[i];
    }
    ~prescription()
    {
        delete[] medicinePtr;
    }
};
//room class
class Room {
protected:
    int roomNumber;
    string roomType;
    bool isOccupied;
public:
    Room()
    {
        roomNumber = 0;
        roomType = "General";
        isOccupied = false;
    }
    Room(int number, string type, bool occupied = false)
    {
        roomNumber = number;
        roomType = type;
        isOccupied = occupied;
    }
    virtual ~Room() {
        cout << "Room destructor called" << endl;
    }
    void setNumber(int number)
    {
        roomNumber = number;
    }
    void setType(string type)
    {
        roomType = type;
    }
    string getType()
    {
        return roomType;
    }
    int getNumber()
    {
        return roomNumber;
    }
    void setIsOccupied(bool occupied)
    {
        isOccupied = occupied;
    }
    bool getIsOccupied()
    {
        return isOccupied;
    }
    virtual void bookRoom()
    {
        if (isOccupied)
            cout << "Room is already occupied" << endl;
        else {
            isOccupied = true;
            cout << "Room booked successfully" << endl;
        }
    }
    virtual void releaseRoom()
    {
        if (isOccupied)
        {
            isOccupied = false;
            cout << "Room released successfully" << endl;
        }
        else cout << "Room is already vacant" << endl;
    }
    virtual void displayRoomInfo()
    {
        cout << "Room Info" << endl;
        cout << "Room Number: " << roomNumber << endl;
        cout << "Room Type: " << roomType << endl;
        cout << "Is Occupied: " << (isOccupied ? "Yes" : "No") << endl;
    }
};
//room type
class ICURoom : public Room {
    const int capacity = 30;
    bool hasVentilator;
    int patientCount;
public:
    ICURoom() : Room() {
        hasVentilator = false;
        patientCount = 0;
    }
    ICURoom(int number, string type, bool occupied, bool ventilator) : Room(number, type, occupied) {
        hasVentilator = ventilator;
        patientCount = 0;
    }
    int getCapacity()
    {
        return capacity;
    }
    void setHasVentilator(bool ventilator) {
        hasVentilator = ventilator;
    }
    bool getHasVentilator() {
        return hasVentilator;
    }
    void bookRoom() override {
        if (patientCount < capacity)
        {
            patientCount++;
            setIsOccupied(true);
            cout << "Patient admitted to ICU Room successfully" << endl;
        }
        else
        {
            cout << "ICU Room is at full capacity" << endl;
        }
    }
};
//room type
class GeneralRoom : public Room {
private:
    const int capacity = 50;
    int patientCount;
public:
    GeneralRoom() : Room() {
        patientCount = 0;
    }
    GeneralRoom(int number, string type, bool occupied) : Room(number, type, occupied) {
        patientCount = 0;
    }
    int getCapacity()
    {
        return capacity;
    }
    void bookRoom() override
    {
        if (patientCount < capacity)
        {
            patientCount++;
            setIsOccupied(true);
            cout << "Patient admitted to General Room successfully" << endl;
        }
        else
        {
            cout << "General Room is at full capacity" << endl;
        }
    }
};
//room type
class EmergencyRoom : public Room {
private:
    const int capacity = 10;
    int patientCount;
public:
    EmergencyRoom() : Room() {
        patientCount = 0;
    }
    EmergencyRoom(int number, string type, bool occupied) : Room(number, type, occupied) {
        patientCount = 0;
    }
    int getCapacity()
    {
        return capacity;
    }
    void bookRoom() override
    {
        if (patientCount < capacity)
        {
            patientCount++;
            setIsOccupied(true);
            cout << "Patient admitted to Emergency Room successfully" << endl;
        }
        else
        {
            cout << "Emergency Room is at full capacity" << endl;
        }
    }
};
//appointment scheduling class
class appointmentScheduling {
    string appointmentDate;
    string appointmentTime;
    string doctorSpecialization;
    bool ifBooked;
    patient* currentPatient;
    doctor* selectedDoctor;
public:
    appointmentScheduling() {
        appointmentDate = "";
        appointmentTime = "";
        doctorSpecialization = " ";
        ifBooked = false;
        currentPatient = NULL;
        selectedDoctor = NULL;
    }
    // Function updated to use aggregation (passing patient and doctor array)
    void scheduleAppointment(patient& p, doctor Doctors[], int s) {
        cout << "Welcome: " << p.getcommonpersonName() << endl;
        cout << "Please book your appointment" << endl;
        cout << "Select doctor specialization: " << endl;
        cout << "1. General\n2. Surgeon\n3. Cardiologist" << endl;
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        string Byname = "";
        if (choice == 1)
        {
            Byname = "General";
        }
        else if (choice == 2)
        {
            Byname = "Surgeon";
        }
        else if (choice == 3)
        {
            Byname = "Cardiologist";
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
            return;
        }
        cout << "Available Doctors for " << Byname << ":" << endl;
        for (int i = 0; i < s; i++) {
            if (Doctors[i].getdoctorType() == Byname) {
                cout << "  " << Doctors[i].getcommonpersonName() << "  " << Doctors[i].getdoctorStatus() << " " << Doctors[i].getdoctorType() << " " << endl;
            }
        }
        scheduleByname(p, Doctors, s);
    }
    void scheduleByname(patient& p, doctor Doctors[], int s) {
        currentPatient = &p;
        cout << "Welcome: " << p.getcommonpersonName() << endl;
        cout << "Enter doctor name to schedule appointment: ";
        string name;
        cin >> name;
        cout << "Enter day of appointment:";
        string day;
        cin >> day;
        for (int i = 0; i < s; i++) {
            if (Doctors[i].getcommonpersonName() == name)
            {
                if (Doctors[i].getdoctorStatus() == "free")
                {
                    Doctors[i].setdoctorStatus("busy");
                    Doctors[i].setappointmentStatus(true);
                    if (Doctors[i].getappdetailptr() == NULL) {
                        Doctors[i].setappdetailptr(new appointmentDetail());
                    }
                    Doctors[i].setappointmentbyName(p.getcommonpersonName());
                    Doctors[i].setappointmentbyId(p.getcommonpersonID());
                    Doctors[i].setappointmenttoName(Doctors[i].getcommonpersonName());
                    Doctors[i].setappointmenttoId(Doctors[i].getcommonpersonID());
                    Doctors[i].setappointmentDay(day); //this is based on user input
                    this->selectedDoctor = &Doctors[i];
                    this->ifBooked = true;
                    this->doctorSpecialization = Doctors[i].getdoctorType();
                    cout << "Appointment booked successfully with Dr. " << Doctors[i].getcommonpersonName() << endl;
                    successfulAppointment();
                    return;
                }
                else {
                    cout << "Dr. " << Doctors[i].getcommonpersonName() << " is currently busy." << endl;
                    return;
                }
            }
        }
        cout << "Doctor not found." << endl;
    }
    void successfulAppointment() {
        if (ifBooked && selectedDoctor != NULL && currentPatient != NULL) {
            cout << " Appointment Booked" << endl;
            cout << "Patient: " << currentPatient->getcommonpersonName() << endl;
            cout << "Doctor: " << selectedDoctor->getcommonpersonName() << endl;
            cout << "Specialization: " << doctorSpecialization << endl;
            cout << "Status: Confirmed" << endl;
        }
        else
        {
            cout << "No appointment has been booked yet." << endl;
        }
    }
};
//functions for admin portal 


//Pharmacy
class Pmedicine {
    string name;
    string type;
    int quantity;
    float price;
public:
    Pmedicine() {
        name = "";
        type = "";
        quantity = 0;
        price = 0.0;
    }
    Pmedicine(string n, string t, int q, float p) {
        name = n;
        type = t;
        quantity = q;
        price = p;
    }
    void setName(string n) {
        name = n;
    }
    void setType(string t) {
        type = t;
    }
    void setQuantity(int q) {
        if (q >= 0)
            quantity = q;
    }
    void setPrice(float p) {
        price = p;
    }
    string getName() {
        return name;
    }
    string getType() {
        return type;
    }
    int getQuantity() {
        return quantity;
    }
    float getPrice() {
        return price;
    }

    bool isQuantityEnough(int requiredQ) {
        if (quantity >= requiredQ) {
            return true;
        }
        else {
            return false;
        }
    }
    void reduceStock(int q) {
        if (q <= quantity) {
            quantity -= q;
        }
        else {
            quantity = 0;
        }
    }
    void display() {
        cout << "Name: " << name << endl;
        cout << "Type: " << type << endl;
        cout << "Quantity: " << quantity << endl;
        cout << "Price: " << price << endl;
    }


};
class ReorderRequest {
    string name;
    string type;
    int quantityNeeded;

public:
    ReorderRequest() {
        name = "";
        type = "";
        quantityNeeded = 0;
    }

    ReorderRequest(string n, string t, int q) {
        name = n;
        type = t;
        quantityNeeded = q;
    }

    void setData(string n, string t, int q) {
        name = n;
        type = t;
        quantityNeeded = q;
    }

    void display() {
        cout << "Reordering " << name
            << " of Type " << type
            << " and Qty: " << quantityNeeded << endl;
    }
    string getName() {
        return name;
    }

    string getType() {
        return type;
    }

    int getQuantity() {
        return quantityNeeded;
    }
};
class Pharmacy {
private:
    // Medicine Inventory
    Pmedicine* inventory;
    int medCount;
    int medCapacity;
    //list of Purchased Medicines (for billing)
    Pmedicine* purchased;
    int purchasedCount;
    ReorderRequest* requests;
    int requestCount;
    int requestCapacity;


public:
    Pharmacy() {
        medCapacity = 100;
        medCount = 0;
        purchasedCount = 0;
        inventory = new Pmedicine[medCapacity];
        purchased = new Pmedicine[100];

        requestCapacity = 50;
        requestCount = 0;
        requests = new ReorderRequest[requestCapacity];

    }
    ~Pharmacy() {
        delete[] inventory;
        delete[] purchased;
        delete[] requests;

    }

    // ----------- POINT 1: GETTER FOR BILLING -----------
    Pmedicine* getPurchasedList() {
        return purchased;
    }

    int getPurchasedCount() {
        return purchasedCount;
    }


    void clearPurchasedCart() {
        purchasedCount = 0;
    }
    void addMedicine(Pmedicine m) {
        if (medCount < medCapacity) {
            inventory[medCount] = m;
            medCount++;
        }
    }


    int findMedicine(string name) {
        for (int i = 0; i < medCount; i++) {
            if (inventory[i].getName() == name) {
                return i;
            }
        }
        return -1;
    }
    bool isAvailable(string name) {
        if (findMedicine(name) != -1)
        {
            return true;
        }
        else {
            return false;
        }
    }
    void sendReorder(string name, string type, int qty) {
        if (requestCount < requestCapacity) {
            requests[requestCount].setData(name, type, qty);
            requestCount++;

            ofstream outfile("reorders.txt", ios::app);
            outfile << name << "," << type << "," << qty << endl;
            outfile.close();
        }
    }
    //to process the prescription and for the overall working of the pharmacy
    void presProcess(prescription& p) {
        for (int i = 0; i < p.getCount(); i++)
        {
            string n = p.getMedicine(i).getmedicineName();
            int reqQty = p.getMedicine(i).getmedicineQuantity();

            int index = findMedicine(n);
            if (index == -1)
            {
                cout << "    Med not available" << endl;
                sendReorder(n, "unknown", reqQty);
                continue;
            }
            if (inventory[index].isQuantityEnough(reqQty)) {
                //reduction from the stock if available
                inventory[index].reduceStock(reqQty);
                //adding object to purchased array so that bill can be generated
                purchased[purchasedCount] = inventory[index];
                purchased[purchasedCount].setQuantity(reqQty);
                purchasedCount++;
            }
            else {
                //if less quantity than required is available or no quantity available
                int available = inventory[index].getQuantity();

                if (available > 0) {
                    cout << "Only available quantity is " << available << endl;
                    purchased[purchasedCount] = inventory[index];
                    purchased[purchasedCount].setQuantity(available);
                    purchasedCount++;

                    inventory[index].reduceStock(available);
                    sendReorder(n, inventory[index].getType(), reqQty - available);
                }
                else {
                    cout << "Out of stock" << endl;
                    sendReorder(n, inventory[index].getType(),
                        reqQty);
                }
            }
        }
        saveToFile("medicine.txt");
    }
    void showInventory() {
        for (int i = 0; i < medCount; i++) {
            cout << inventory[i].getName() << " - "
                << inventory[i].getQuantity() << endl;
        }
    }
    void showReorders() {
        for (int i = 0; i < requestCount; i++) {
            requests[i].display();
        }
    }
    void loadFromFile(string filename) {
        ifstream infile(filename);
        if (!infile) {
            cout << "Error file cant be open" << endl;
            return;
        }

        string line;
        while (getline(infile, line)) {
            int x;// current postion on the line

            x = line.find(',');
            string name = line.substr(0, x);
            line = line.substr(x + 1);

            x = line.find(',');
            string type = line.substr(0, x);
            line = line.substr(x + 1);

            x = line.find(',');
            int quantity = stoi(line.substr(0, x));
            line = line.substr(x + 1);

            float price = stof(line);

            addMedicine(Pmedicine(name, type, quantity, price));
        }

        infile.close();
    }
    void saveToFile(string filename) {
        ofstream outfile(filename);

        for (int i = 0; i < medCount; i++) {
            outfile << inventory[i].getName() << ","
                << inventory[i].getType() << ","
                << inventory[i].getQuantity() << ","
                << inventory[i].getPrice() << endl;
        }

        outfile.close();
    }



};


void addDoctor(doctor*& Doctors, int& s, int& cap) {
    if (s >= cap) {
        cap = cap + 3;
        doctor* newArr = new doctor[cap];
        for (int i = 0; i < s; i++) {
            newArr[i] = Doctors[i];
        }
        delete[] Doctors;
        Doctors = newArr;
    }
    ofstream outFile("doctors.txt", ios::app);
    if (!outFile) {
        cout << "Error opening file." << endl;
        return;
    }
    else
    {
        cout << "Enter doctor ID: ";
        string id;
        cin >> id;
        cout << "Enter doctor name: ";
        string name;
        cin >> name;
        cout << "Enter doctor age: ";
        int age;
        cin >> age;
        cout << "Enter doctor specialization: ";
        string type;
        cin >> type;
        cout << "Enter doctor status: ";
        string status;
        cin >> status;
        cout << "Enter doctor fee: ";
        int fee;
        cin >> fee;
        cout << "Enter doctor salary: ";
        int salary;
        cin >> salary;
        Doctors[s] = doctor(id, name, age, type, status, fee, salary, false, NULL);
        outFile << "Name: " << name << ", ID: " << id << ", Age: " << age << ", Type: " << type << ", Fee: " << fee << ", Salary: " << salary << endl;
        s++;
        outFile.close();
    }
}
void viewDoctors(doctor Doctors[], int s)
{
    cout << "List of Doctors:" << endl;
    for (int i = 0; i < s; i++) {
        cout << "Name: " << Doctors[i].getcommonpersonName() << "  Specialization: " << Doctors[i].getdoctorType() << " Status: " << Doctors[i].getdoctorStatus() << endl;
    }
}
void removeDoctor(doctor Doctors[], int& s) {
    cout << "Enter doctor ID to remove: ";
    string id;
    cin >> id;
    for (int i = 0; i < s; i++) {
        if (Doctors[i].getcommonpersonID() == id) {
            for (int j = i; j < s - 1; j++) {
                Doctors[j] = Doctors[j + 1];
            }
            s--;
            ofstream outFile("doctors.txt");
            if (outFile) {
                for (int k = 0; k < s; k++) {
                    outFile << "Name: " << Doctors[k].getcommonpersonName() << " ID: " << Doctors[k].getcommonpersonID() << " Age: " << Doctors[k].getcommonpersonAge() << " Type: " << Doctors[k].getdoctorType() << " Fee: " << Doctors[k].getdoctorFee() << " Salary: " << Doctors[k].getdoctorSalary() << endl;
                }
                outFile.close();
            }
            cout << "Doctor removed successfully." << endl;
            return;
        }
    }
    cout << "Doctor not found." << endl;
}
void seePatientDetails(patient Patients[], int s) {
    cout << "List of Patients:" << endl;
    for (int i = 0; i < s; i++) {
        cout << "Name: " << Patients[i].getcommonpersonName() << "  Age: " << Patients[i].getcommonpersonAge() << " Type: " << Patients[i].getpatientType() << endl;
    }
}
void seeRoomDetails(Room* rooms[], int s) {
    cout << "List of Rooms:" << endl;
    for (int i = 0; i < s; i++) {
        rooms[i]->displayRoomInfo();
        cout << endl;
    }
}
void seeAppointmentDetails(appointmentScheduling& scheduler) {
    cout << "Appointment Details:" << endl;
    scheduler.successfulAppointment();
}
void editPatientDetails(patient Patients[], int s) {
    cout << "Enter patient name to edit: ";
    string name;
    cin >> name;
    for (int i = 0; i < s; i++) {
        if (Patients[i].getcommonpersonName() == name) {
            cout << "Editing details for " << name << endl;
            int age;
            string type;
            cout << "New Age: ";
            cin >> age;
            cout << "New Type: ";
            cin >> type;
            Patients[i].setcommonpersonAge(age);
            Patients[i].setpatientType(type);
            cout << "Patient details updated successfully." << endl;
            return;
        }
    }
    cout << "Patient not found." << endl;
}
void editDoctorDetails(doctor Doctors[], int s) {
    cout << "Enter doctor name to edit: ";
    string name;
    cin >> name;
    for (int i = 0; i < s; i++) {
        if (Doctors[i].getcommonpersonName() == name) {
            cout << "Editing details for Dr. " << name << endl;
            string type, status;
            int fee, salary;
            cout << "New Specialization: ";
            cin >> type;
            cout << "New Status: ";
            cin >> status;
            cout << "New Fee: ";
            cin >> fee;
            cout << "New Salary: ";
            cin >> salary;
            Doctors[i].setdoctorType(type);
            Doctors[i].setdoctorStatus(status);
            Doctors[i].setdoctorFee(fee);
            Doctors[i].setdoctorSalary(salary);
            cout << "Doctor details updated successfully." << endl;
            return;
        }
    }
    cout << "Doctor not found." << endl;
}
void editSpecialization(doctor Doctors[], int s) {
    cout << "Enter doctor name to edit specialization: ";
    string name;
    cin >> name;
    for (int i = 0; i < s; i++) {
        if (Doctors[i].getcommonpersonName() == name) {
            cout << "Editing specialization for Dr. " << name << endl;
            string type;
            cout << "New Specialization: ";
            cin >> type;
            Doctors[i].setdoctorType(type);
            cout << "Doctor specialization changed successfully." << endl;
            return;
        }
    }
    cout << "Doctor not found." << endl;
}
void editStatus(doctor Doctors[], int s) {
    cout << "Enter doctor name to edit status: ";
    string name;
    cin >> name;
    for (int i = 0; i < s; i++) {
        if (Doctors[i].getcommonpersonName() == name) {
            cout << "Editing status for Dr. " << name << endl;
            string status;
            cout << "New Status: ";
            cin >> status;
            Doctors[i].setdoctorStatus(status);
            cout << "Doctor status changed successfully." << endl;
            return;
        }
    }
    cout << "Doctor not found." << endl;
}
void editFee(doctor Doctors[], int s) {
    cout << "Enter doctor name to edit fee: ";
    string name;
    cin >> name;
    for (int i = 0; i < s; i++) {
        if (Doctors[i].getcommonpersonName() == name) {
            cout << "Editing fee for Dr. " << name << endl;
            int fee;
            cout << "New Fee: ";
            cin >> fee;
            Doctors[i].setdoctorFee(fee);
            cout << "Doctor fee changed successfully." << endl;
            return;
        }
    }
    cout << "Doctor not found." << endl;
}
void editSalary(doctor Doctors[], int s) {
    cout << "Enter doctor name to edit salary: ";
    string name;
    cin >> name;
    for (int i = 0; i < s; i++) {
        if (Doctors[i].getcommonpersonName() == name) {
            cout << "Editing salary for Dr. " << name << endl;
            int salary;
            cout << "New Salary: ";
            cin >> salary;
            Doctors[i].setdoctorSalary(salary);
            cout << "Doctor salary changed successfully." << endl;
            return;
        }
    }
    cout << "Doctor not found." << endl;
}
void adminPortal(doctor*& Doctors, patient*& Patients, Room* rooms[], int room_c, appointmentScheduling& scheduler, int& ds, int& ps, int& dcap, int& pcap) {
    cout << "Welcome to the Admin Portal" << endl;
    cout << "1. Add Doctor" << endl;
    cout << "2. View Doctors" << endl;
    cout << "3. Remove Doctor" << endl;
    cout << "4. see patient details" << endl;
    cout << "5. see room details" << endl;
    cout << "6. see appointment details" << endl;
    cout << "7. edit doctor details" << endl;
    cout << "8. edit patient details" << endl;
    cout << "9. exit" << endl;
    int choice;
    cout << "Enter your choice: ";
    cin >> choice;
    if (choice == 1) {
        cout << "Adding a new doctor" << endl;
        addDoctor(Doctors, ds, dcap);
    }
    else if (choice == 2)
    {
        cout << "Viewing all doctors" << endl;
        viewDoctors(Doctors, ds);
    }
    else if (choice == 3)
    {
        cout << "Removing a doctor" << endl;
        removeDoctor(Doctors, ds);
    }
    else if (choice == 4)
    {
        cout << "Viewing patient details" << endl;
        seePatientDetails(Patients, ps);
    }
    else if (choice == 5)
    {
        cout << "Viewing room details" << endl;
        seeRoomDetails(rooms, room_c);
    }
    else if (choice == 6)
    {
        cout << "Viewing appointment details" << endl;
        seeAppointmentDetails(scheduler);
    }
    else if (choice == 7)
    {
        cout << "Editing doctor details" << endl;
        cout << "What details do you want to edit?" << endl;
        cout << "1. Specialization" << endl;
        cout << "2. Status" << endl;
        cout << "3. Fee" << endl;
        cout << "4. Salary" << endl;
        cout << "5. All details" << endl;
        cout << "6.Exit" << endl;
        cout << "Enter your choice: ";
        int Choice;
        cin >> Choice;
        if (Choice == 1)
        {
            editSpecialization(Doctors, ds);
        }
        else if (Choice == 2)
        {
            editStatus(Doctors, ds);
        }
        else if (Choice == 3)
        {
            editFee(Doctors, ds);
        }
        else if (Choice == 4)
        {
            editSalary(Doctors, ds);
        }
        else if (Choice == 5)
        {
            editDoctorDetails(Doctors, ds);
        }
        else if (Choice == 6)
        {
            cout << "Exiting doctor details editing" << endl;
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
    else if (choice == 8)
    {
        cout << "Editing patient details" << endl;
        editPatientDetails(Patients, ps);
    }
    else
    {
        cout << "Invalid choice. Please try again." << endl;
    }
}
void viewAllpatients(patient Patients[], int s) {
    cout << "List of Patients:" << endl;
    for (int i = 0; i < s; i++) {
        cout << "Name: " << Patients[i].getcommonpersonName() << "  Age: " << Patients[i].getcommonpersonAge() << " Type: " << Patients[i].getpatientType() << endl;
    }
}
void viewHealthRecord(patient Patients[], int s) {
    cout << "Enter patient name to view health record: ";
    string name;
    cin >> name;
    for (int i = 0; i < s; i++) {
        if (Patients[i].getcommonpersonName() == name) {
            cout << "Health Record for " << name << endl;
            cout << "Symptoms: " << Patients[i].getSymptoms() << endl;
            cout << "Diagnosis: " << Patients[i].getDiagnosis() << endl;
            return;
        }
    }
    cout << "Patient not found." << endl;
}
void viewPrescription(patient Patients[], int s) {
    cout << "Enter patient name to view prescription: ";
    string name;
    cin >> name;
    for (int i = 0; i < s; i++) {
        if (Patients[i].getcommonpersonName() == name) {
            cout << "Prescription for " << name << endl;
            cout << "Patient Name: " << Patients[i].getcommonpersonName() << endl;
            cout << "Patient ID: " << Patients[i].getcommonpersonID() << endl;
            cout << "Patient Age: " << Patients[i].getcommonpersonAge() << endl;
            cout << "Patient Diagnosis: " << Patients[i].getDiagnosis() << endl;
            return;
        }
    }
    cout << "Patient not found." << endl;
}
void setStatus(doctor Doctors[], int s) {
    cout << "Enter doctor name to set status: ";
    string name;
    cin >> name;
    for (int i = 0; i < s; i++) {
        if (Doctors[i].getcommonpersonName() == name) {
            cout << "Setting status for Dr. " << name << endl;
            string status;
            cout << "New Status: ";
            cin >> status;
            Doctors[i].setdoctorStatus(status);
            cout << "Doctor status changed successfully." << endl;
            return;
        }
    }
    cout << "Doctor not found." << endl;
}
void setFee(doctor Doctors[], int s) {
    cout << "Enter doctor name to set fee: ";
    string name;
    cin >> name;
    for (int i = 0; i < s; i++) {
        if (Doctors[i].getcommonpersonName() == name) {
            cout << "Setting fee for Dr. " << name << endl;
            int fee;
            cout << "New Fee: ";
            cin >> fee;
            Doctors[i].setdoctorFee(fee);
            cout << "Doctor fee changed successfully." << endl;
            return;
        }
    }
    cout << "Doctor not found." << endl;
}
void seeAppointments(appointmentScheduling& scheduler) {
    cout << "Viewing appointments" << endl;
    scheduler.successfulAppointment();
}
void addPatient(patient*& Patients, int& s, int& capa) {
    if (s >= capa) {
        capa = capa + 3;
        patient* newArr = new patient[capa];
        for (int i = 0; i < s; i++) {
            newArr[i] = Patients[i];
        }
        delete[] Patients;
        Patients = newArr;
    }
    ofstream outFile("patients.txt", ios::app);
    if (!outFile) {
        cout << "Error opening file." << endl;
        return;
    }
    else
    {
        cout << "Enter patient ID" << endl;
        string id;
        cin >> id;
        cout << "Enter patient symptoms" << endl;
        string symptom;
        cin >> symptom;
        cout << "Enter the patient diagnosis" << endl;
        string diagnose;
        cin >> diagnose;
        cout << "Enter patient name: ";
        string name;
        cin >> name;
        cout << "Enter patient age: ";
        int age;
        cin >> age;
        cout << "Enter patient type: ";
        string type;
        cin >> type;
        Patients[s] = patient(id, name, age, type, symptom, diagnose);
        outFile << "Name: " << name << ", ID: " << id << ", Age: " << age << ", Type: " << type << ", Symptoms: " << symptom << ", Diagnosis: " << diagnose << endl;
        s++;
        outFile.close();
    }
}
void removePatient(patient*& Patients, int& s) {
    cout << "Enter patient name to remove: ";
    string name;
    cin >> name;
    for (int i = 0; i < s; i++) {
        if (Patients[i].getcommonpersonName() == name) {
            for (int j = i; j < s - 1; j++) {
                Patients[j] = Patients[j + 1];
            }
            s--;
            cout << "Patient " << name << " removed successfully." << endl;
            return;
        }
    }
    cout << "Patient not found." << endl;
}
void applyLeave(doctor Doctors[], int s) {
    cout << "Enter doctor name to apply for leave: ";
    string name;
    cin >> name;
    for (int i = 0; i < s; i++) {
        if (Doctors[i].getcommonpersonName() == name) {
            cout << "Applying for leave for Dr. " << name << endl;
            string status = "on leave";
            Doctors[i].setdoctorStatus(status);
            cout << "Doctor " << name << " is now on leave." << endl;
            return;
        }
    }
    cout << "Doctor not found." << endl;
}
void doctorPortal(doctor*& Doctors, patient*& Patients, Room* rooms[], appointmentScheduling& scheduler, int& doc_s, int& pat_s, int& doc_capa, int& pat_capa) {
    cout << "Welcome to the Doctor Portal" << endl;
    int choice = 0;
    while (choice != 10) {
        cout << "Press key to perform task " << endl;
        cout << "1. View all Patients" << endl;
        cout << "2. View Patient's Health Record" << endl;
        cout << "3. View Patient's Prescription" << endl;
        cout << "4. Set your Status" << endl;
        cout << "5. Set your Fee" << endl;
        cout << "6. See your appointments" << endl;
        cout << "7. Add Patient" << endl;
        cout << "8. Remove Patient" << endl;
        cout << "9. Apply for Leave" << endl;
        cout << "10. exit " << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            viewAllpatients(Patients, pat_s);
            break;
        case 2:
            viewHealthRecord(Patients, pat_s);
            break;
        case 3:
            viewPrescription(Patients, pat_s);
            break;
        case 4:
            setStatus(Doctors, doc_s);
            break;
        case 5:
            setFee(Doctors, doc_s);
            break;
        case 6:
            seeAppointments(scheduler);
            break;
        case 7:
            addPatient(Patients, pat_s, pat_capa);
            break;
        case 8:
            removePatient(Patients, pat_s);
            break;
        case 9:
            applyLeave(Doctors, doc_s);
            break;
        default:
            cout << "work" << endl;
        }
    }
    cout << "Thanks you for visiting..." << endl;
}

// new sig
void patientPortal(doctor* Doctors, int docSize, Pharmacy& pharm)
{
    int choice = 0;
    while (choice != 8)
    {
        cout << "----------------Welcome To The Patient Portal----------------------" << endl;
        cout << "Press key to perform task " << endl;
        cout << "1. View all Doctors" << endl; // done 
        cout << "2. Book an appointment" << endl; // done 
        cout << "3. View Health Record" << endl; // done 
        cout << "4. View Pescription" << endl;
        cout << "5. Buy Medicine" << endl;
        cout << "6. Fill a complain" << endl;
        cout << "7. Fill a suggestion" << endl;
        cout << "8. Exit" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            // viewDoctors(d, doctorSize); 
            break;
        case 2:
            //as->scheduleAppointment( p , d , doctorSize); 
            break;
        case 3:
            //  p.getRecord(); 
            break;
        case 4:
            // prescription 
            break;
        case 5:
            //pharmacy integration 
            break;
        case 6:
            // after maing admin class
            break;
        case 7:
            //after making class 
            break;
        default:
            cout << "work" << endl;
        }
    }

    cout << "Thanks you for visiting..." << endl;
}
bool passwordChecker(string pass)
{
    if (pass.length() <= 10)
    {
        return true;
    }
    else
        return false;
}
bool idsizeChecker(string id)
{
    if (id.length() == 4)
        return true;
    else
        return false;
}
bool idVerifier(string checkingID, string file)
{
    bool uniqueID = true;
    string fileID;
    string word;
    string filename;

    filename = file;
    ifstream infile(filename);
    if (!infile)
    {
        cout << "Cannot Open File" << endl;
    }
    while (getline(infile, word))
    {
        int positionofComma = word.find(',');
        if (positionofComma == string::npos)
        {
            continue;
        }
        else
        {
            fileID = word.substr(0, positionofComma);
            if (fileID == checkingID)
            {
                uniqueID = false;
                break;
            }
        }
    }
    if (!uniqueID)
    {
        return false;
    }
    else
    {
        return true;
    }
}
//registration portal 
bool registrationportal(string name, string file)
{
    string loginID, loginPass;
    string fileID, filePass;
    int choice = 0;
    string filename;
    string word;
    bool idValidation = false;
    bool passValidation = false;
    bool formatValidation = true;
    cout << "-----" << name << " registration-----" << endl;
    while (choice != 3)
    {
        cout << "Enter your choice to continue" << endl;
        cout << "1. Login" << endl;
        cout << "2. Sign Up" << endl;
        cout << "3. Exit" << endl;
        cin >> choice;
        if (choice == 1)
        {
            idValidation = false;
            passValidation = false;
            cout << "Enter your id :";
            cin >> loginID;
            cout << "Enter your password :";
            cin >> loginPass;
            filename = file;
            ifstream infile(filename);
            if (!infile)
            {
                cout << "Cannot Open File" << endl;
            }
            while (getline(infile, word)) // infile.eof()
            {

                int positionofComma = word.find(',');
                if (positionofComma == string::npos)
                {
                    continue;
                }
                else
                {
                    fileID = word.substr(0, positionofComma);
                    filePass = word.substr(positionofComma + 1);
                    if (fileID == loginID)
                    {
                        idValidation = true;
                        if (filePass == loginPass)
                        {
                            passValidation = true;
                            break;
                        }
                        else
                            passValidation = false;
                    }
                }

            }

            if (!idValidation)
            {
                cout << "Invalid User ID...Re-enter or Sign Up to continue" << endl;
            }
            if (!passValidation && idValidation)
            {
                cout << "Invalid Password...Try Again" << endl;
            }

            infile.close();
            if (passValidation && idValidation)
            {
                return true;
            }

        }
        else if (choice == 2)
        {
            bool registrationSuccessful = false;
            string userID;
            string userPass;
            bool isuserpassValid = false;
            bool isuseridsizeValid = false;
            bool isuseridUnique = false;
            cout << "Enter 4 digit ID : ";
            cin >> userID;
            isuseridsizeValid = idsizeChecker(userID);
            if (isuseridsizeValid)
            {
                isuseridUnique = idVerifier(userID, file);
                if (!isuseridUnique)
                {
                    cout << "Id is already taken...Try again" << endl;
                }
                else
                {
                    cout << "Enter Password (max size 10 ) : ";
                    cin >> userPass;
                    isuserpassValid = passwordChecker(userPass);
                    if (isuserpassValid)
                    {
                        filename = file;
                        ofstream outfile(filename, ios::app);
                        if (!outfile)
                        {
                            cout << "Error opening file" << endl;
                        }
                        outfile << endl << userID << "," << userPass;
                        outfile.close();
                        cout << "User added successfully" << endl; //create object with information 
                        // patientsdata.txt
                        // doctordata.txt
                        registrationSuccessful = true;
                        cout << "Log in to continue" << endl;

                    }
                    else
                        cout << "Invalid Pass...Try Again" << endl;
                }
            }
            else
                cout << "Invalid ID size...Try again" << endl;

        }
        else if (choice != 3)
        {
            cout << "Invalid Choice...Enter Again " << endl;
        }
    }
    cout << "Thank you for visiting" << endl;
    return false;
}
//bootup (Updated bootup)
void bootup(doctor*& docPtr, patient*& patPtr, int& docSize, int& patSize, Pharmacy& pharm)
{// Load Pharmacy Inventory
    pharm.loadFromFile("medicine.txt");


    int loopController = 0;
    string dummy;
    ifstream infilecountingdoc("doctor.txt");
    if (!infilecountingdoc)
    {
        cout << "Cannot open file" << endl;
    }
    while (getline(infilecountingdoc, dummy))
    {
        docSize++;
    }
    infilecountingdoc.close();
    docPtr = new doctor[docSize];
    ifstream infilecountingpatient("patient.txt");
    if (!infilecountingpatient)
    {
        cout << "Cannot open file" << endl;
    }
    while (getline(infilecountingpatient, dummy))
    {
        patSize++;
    }
    infilecountingpatient.close();
    patPtr = new patient[patSize];
    // doctor 
    ifstream doctorfile("doctor.txt");
    if (!doctorfile)
    {
        cout << "Cannot open file" << endl;
    }
    while (getline(doctorfile, dummy) && loopController < docSize)
    {


        int pos;
        pos = dummy.find(',');
        string name = dummy.substr(0, pos);
        dummy = dummy.substr(pos + 1);
        pos = dummy.find(',');
        string id = dummy.substr(0, pos);
        dummy = dummy.substr(pos + 1);
        pos = dummy.find(',');
        int age = stoi(dummy.substr(0, pos));
        dummy = dummy.substr(pos + 1);
        pos = dummy.find(',');
        string status = dummy.substr(0, pos);
        dummy = dummy.substr(pos + 1);
        pos = dummy.find(',');
        string type = dummy.substr(0, pos);
        dummy = dummy.substr(pos + 1);
        pos = dummy.find(',');
        int fee = stoi(dummy.substr(0, pos));
        dummy = dummy.substr(pos + 1);
        int salary = stoi(dummy);
        docPtr[loopController].setcommonpersonName(name);
        docPtr[loopController].setcommonpersonID(id);
        docPtr[loopController].setcommonpersonAge(age);
        docPtr[loopController].setdoctorType(type);
        docPtr[loopController].setdoctorStatus(status);
        docPtr[loopController].setdoctorFee(fee);
        docPtr[loopController].setdoctorSalary(salary);
        loopController++;
    }
    doctorfile.close();
    //patient
    ifstream patientfile("patient.txt");
    if (!patientfile)
    {
        cout << "Cannot open file" << endl;
    }
    dummy = " ";
    loopController = 0;
    while (getline(patientfile, dummy) && loopController < patSize)
    {

        int pos;
        pos = dummy.find(',');
        string id = dummy.substr(0, pos);
        dummy = dummy.substr(pos + 1);
        pos = dummy.find(',');
        string name = dummy.substr(0, pos);
        dummy = dummy.substr(pos + 1);
        pos = dummy.find(',');
        int age = stoi(dummy.substr(0, pos));
        dummy = dummy.substr(pos + 1);
        pos = dummy.find(',');
        string type = dummy.substr(0, pos);
        dummy = dummy.substr(pos + 1);
        pos = dummy.find(',');
        string symptom = dummy.substr(0, pos);
        dummy = dummy.substr(pos + 1);
        string diagnosis = dummy;
        patPtr[loopController].setcommonpersonName(name);
        patPtr[loopController].setcommonpersonID(id);
        patPtr[loopController].setcommonpersonAge(age);
        patPtr[loopController].setpatientType(type);
        patPtr[loopController].setSymptoms(symptom);
        patPtr[loopController].setDiagnosis(diagnosis);
        loopController++;
    }
    patientfile.close();


}
//  BILLING FUNCTION MODIFIED TO WORK WITH PMEDICINE 
void generateFinalBill(doctor* assignedDoctor, Pmedicine* meds, int numMeds)
{
    int totalBill = 0;

    cout << "\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";

    cout << "              PATIENT RECIPT              \n";

    cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";

    if (assignedDoctor != nullptr)
    {
        int fee = assignedDoctor->getdoctorFee();

        cout << "Consultation Details:\n";

        cout << "Doctor Specialization : " << assignedDoctor->getdoctorType() << "\n";

        cout << "Consultation Fee      : Rs " << fee << "\n";

        totalBill += fee;
    }

    else
    {
        cout << "No doctor assigned. Consultation Fee: Rs 0\n";
    }

    cout << "------------------------------------------\n";

    cout << "Pharmacy Charges:\n";

    int pharmacyTotal = 0;

    if (meds != nullptr && numMeds > 0)
    {
        for (int i = 0; i < numMeds; i++)
        {
            // Using Pmedicine getters
            int itemTotal = meds[i].getQuantity() * meds[i].getPrice();

            pharmacyTotal += itemTotal;

            cout << "- " << meds[i].getName() << " (" << meds[i].getType() << ")\n";

            cout << "  " << meds[i].getQuantity() << " units @ Rs " << meds[i].getPrice() << " = Rs " << itemTotal << "\n";
        }
    }

    else
    {
        cout << "No medicines purchased.\n";
    }

    cout << "\nPharmacy Subtotal     : Rs " << pharmacyTotal << "\n";

    totalBill += pharmacyTotal;

    cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";

    cout << "TOTAL AMOUNT TO BE PAID     :  RUPEES- " << totalBill << " /- \n";

    cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n\n";
}

int main()
{
    doctor* doctorPtr = nullptr;
    patient* patientPtr = nullptr;

    int doctorSize = 0;
    int patientSize = 0;

    int docCapacity = 100;
    int patCapacity = 100;

    Room* rooms[100];
    int roomCount = 0;

    Pharmacy pharm;
    appointmentScheduling scheduler;

    bool registrationVerifier = false;

    bootup(doctorPtr, patientPtr, doctorSize, patientSize, pharm);

    cout << "-----Welcome to the Hospital Managment System------" << endl;
    int choice = 0;
    while (choice != 4)
    {
        cout << "Enter your Portal number to continue" << endl;
        cout << "1. Admin Portal" << endl;
        cout << "2. Doctor Portal" << endl;
        cout << "3. Patient Portal" << endl;
        cout << "4. Exit" << endl;
        cin >> choice;
        if (choice == 1)
        {
            registrationVerifier = registrationportal("Admin", "AdminPasswords.txt");
            if (registrationVerifier)
            {
                cout << "admin works \n";
                adminPortal(doctorPtr, patientPtr, rooms, roomCount, scheduler, doctorSize, patientSize, docCapacity, patCapacity);
            }
            else
                cout << "Registration Failed" << endl;
        }
        else if (choice == 2)
        {
            registrationVerifier = registrationportal("Doctor", "DoctorPasswords.txt");
            if (registrationVerifier)
            {
                doctorPortal(doctorPtr, patientPtr, rooms, scheduler, doctorSize, patientSize, docCapacity, patCapacity);
            }
            else
                cout << "Registration Failed" << endl;

        }
        else if (choice == 3)
        {
            registrationVerifier = registrationportal("Patient", "PatientPasswords.txt");
            if (registrationVerifier)
            {
                patientPortal(doctorPtr, doctorSize, pharm);
            }
            else
                cout << "Registration Failed" << endl;

        }
        else if (choice != 4)
            cout << "Invalid Choice...Enter Again " << endl;
    }
    cout << "Thank you for visiting" << endl;

    if (doctorPtr != nullptr)
    {
        delete[] doctorPtr;
    }
    if (patientPtr != nullptr)
    {
        delete[] patientPtr;
    }

    return 0;
}