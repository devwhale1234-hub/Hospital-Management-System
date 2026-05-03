#ifndef HOSPITALDATA_H
#define HOSPITALDATA_H

#include <iostream>
#include <string>
#include <fstream>
#include <limits>
using namespace std;

inline string stripCR(string s)
{
    if (!s.empty() && s[s.size() - 1] == '\r')
        s.erase(s.size() - 1);
    return s;
}

inline int getIntInput() {
    int x;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a valid number: ";
    }
    return x;
}

inline string toLowerStr(string str) {
    string lower = "";
    for (char c : str) {
        if (c >= 'A' && c <= 'Z') lower += (c + 32);
        else lower += c;
    }
    return lower;
}

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
    void setappointmentbyName(string name) { appointmentbyName = name; }
    void setappointmentbyId(string id) { appointmentbyId = id; }
    void setappointmenttoName(string name) { appointmenttoName = name; }
    void setappointmenttoId(string id) { appointmenttoId = id; }
    void setappointmentDay(string day) { appointmentDay = day; }
    string getappointmentbyName() { return appointmentbyName; }
    string getappointmentbyId() { return appointmentbyId; }
    string getappointmenttoName() { return appointmenttoName; }
    string getappointmenttoId() { return appointmenttoId; }
    string getappointmentDay() { return appointmentDay; }
};

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
    healthRecords(string symptom, string diagnose) : symptoms(symptom), diagnosis(diagnose) {}
    void setSymptoms(string symptom) { symptoms = symptom; }
    void setDiagnosis(string diagnose) { diagnosis = diagnose; }
    string getSymptoms() { return symptoms; }
    string getDiagnosis() { return diagnosis; }
};

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
    void setcommonpersonID(string id) { common_person_id = id; }
    void setcommonpersonName(string name) { common_person_name = name; }
    void setcommonpersonAge(int age) { common_person_age = age; }
    string getcommonpersonID() { return common_person_id; }
    int getcommonpersonAge() { return common_person_age; }
    string getcommonpersonName() { return common_person_name; }
};

class patient : public common_person
{
    string patientType;
    healthRecords record;
public:
    patient()
    {
        patientType = "General";
    }
    patient(string id, string name, int age, string type, string symptom, string diagnose)
        : common_person(id, name, age), patientType(type), record(symptom, diagnose) {}
    patient(patient& p)
    {
        this->setcommonpersonID(p.getcommonpersonID());
        this->setcommonpersonName(p.getcommonpersonName());
        this->setcommonpersonAge(p.getcommonpersonAge());
        this->patientType = p.patientType;
        this->record = p.record;
    }
    void setpatientType(string type) { patientType = type; }
    void setSymptoms(string symptom) { record.setSymptoms(symptom); }
    void setDiagnosis(string diagnose) { record.setDiagnosis(diagnose); }
    void setRecord(healthRecords& h) { record = h; }
    healthRecords& getRecord() { return record; }
    string getSymptoms() { return record.getSymptoms(); }
    string getDiagnosis() { return record.getDiagnosis(); }
    string getpatientType() { return patientType; }
    void display()
    {
        cout << "Patient Information" << endl;
        cout << "Patient name : " << this->getcommonpersonName() << endl;
        cout << "patient id : " << this->getcommonpersonID() << endl;
        cout << "Patient Age : " << this->getcommonpersonAge() << endl;
        cout << "Patient Type : " << patientType << endl;
        cout << "Patient Health Record " << endl;
        cout << "Patient Symptoms : " << getSymptoms() << endl;
        cout << "Patient Diagnosis : " << getDiagnosis() << endl;
    }
};

class admin : public common_person
{
    string checkSuggestion;
    string checkComplain;
};

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
    doctor(string id, string name, int age, string type, string status, int fee, int salary, bool app_status, appointmentDetail* ap)
        : common_person(id, name, age), doctorType(type), doctorStatus(status), doctorFee(fee), doctorSalary(salary), appointmentStatus(app_status), appdetailPtr(ap) {}
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
            this->appdetailPtr = new appointmentDetail(*d.appdetailPtr);
        else
            this->appdetailPtr = NULL;
    }
    void setdoctorType(string type) { doctorType = type; }
    void setdoctorStatus(string status) { doctorStatus = status; }
    void setappointmentStatus(bool status) { appointmentStatus = status; }
    bool getappointmentStatus() { return appointmentStatus; }
    void setdoctorFee(int fee) { doctorFee = fee; }
    void setdoctorSalary(int Salary) { doctorSalary = Salary; }
    void setappointmentbyName(string name) { appdetailPtr->setappointmentbyName(name); }
    void setappointmentbyId(string id) { appdetailPtr->setappointmentbyId(id); }
    void setappointmenttoName(string name) { appdetailPtr->setappointmenttoName(name); }
    void setappointmenttoId(string id) { appdetailPtr->setappointmenttoId(id); }
    void setappointmentDay(string day) { appdetailPtr->setappointmentDay(day); }
    void setappdetailptr(appointmentDetail* ap) { appdetailPtr = ap; }
    appointmentDetail* getappdetailptr() { return appdetailPtr; }
    string getappointmentbyName() { return appdetailPtr->getappointmentbyName(); }
    string getappointmentbyId() { return appdetailPtr->getappointmentbyId(); }
    string getappointmenttoName() { return appdetailPtr->getappointmenttoName(); }
    string getappointmenttoId() { return appdetailPtr->getappointmenttoId(); }
    string getappointmentDay() { return appdetailPtr->getappointmentDay(); }
    string getdoctorType() { return doctorType; }
    string getdoctorStatus() { return doctorStatus; }
    int getdoctorFee() { return doctorFee; }
    int getdoctorSalary() { return doctorSalary; }
    ~doctor() { delete appdetailPtr; }
};

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
    string getmedicineName() { return name; }
    string getmedicineType() { return medicineType; }
    string getmedicineTime() { return medicineTime; }
    int getmedicineQuantity() { return medicineQuantity; }
    void setmedicineName(string n) { name = n; }
    void setmedicineType(string type) { medicineType = type; }
    void setmedicineQuantity(int num) { medicineQuantity = num; }
    void setmedicineTime(string time) { medicineTime = time; }
};

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
    prescription(doctor* d, patient p, medicine* meds, int num)
    {
        docPtr = d;
        Patient = p;
        numberofmedicines = num;
        if (num > 0)
        {
            medicinePtr = new medicine[num];
            for (int i = 0; i < num; i++)
                medicinePtr[i] = meds[i];
        }
        else
            medicinePtr = NULL;
    }
    void setMedicineAt(int i, string n, string type, int qty, string time)
    {
        if (i >= 0 && i < numberofmedicines)
        {
            medicinePtr[i].setmedicineName(n);
            medicinePtr[i].setmedicineType(type);
            medicinePtr[i].setmedicineQuantity(qty);
            medicinePtr[i].setmedicineTime(time);
        }
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
            cout << "No doctor assigned " << endl;
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
            cout << "Enter medicine : " << i + 1 << endl;
            cout << "Enter medicine Name: ";
            cin >> bufferstring;
            medicinePtr[i].setmedicineName(bufferstring);
            cout << "Enter medicine Type : ";
            cin >> bufferstring;
            medicinePtr[i].setmedicineType(bufferstring);
            cout << "Enter medicine quantity : ";
            bufferint = getIntInput();
            medicinePtr[i].setmedicineQuantity(bufferint);
            cout << "Enter medicine Time: ";
            cin >> bufferstring;
            medicinePtr[i].setmedicineTime(bufferstring);
        }
    }
    void saveToFile(string filename)
    {
        ofstream outfile(filename, ios::app);
        if (outfile)
        {
            for (int i = 0; i < numberofmedicines; i++)
            {
                outfile << Patient.getcommonpersonName() << ","
                    << medicinePtr[i].getmedicineName() << ","
                    << medicinePtr[i].getmedicineType() << ","
                    << medicinePtr[i].getmedicineQuantity() << ","
                    << medicinePtr[i].getmedicineTime() << endl;
            }
            outfile.close();
        }
    }
    int getCount() { return numberofmedicines; }
    medicine getMedicine(int i) { return medicinePtr[i]; }
    ~prescription() { delete[] medicinePtr; }
};

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
    virtual ~Room() {}
    void setNumber(int number) { roomNumber = number; }
    void setType(string type) { roomType = type; }
    string getType() { return roomType; }
    int getNumber() { return roomNumber; }
    void setIsOccupied(bool occupied) { isOccupied = occupied; }
    bool getIsOccupied() { return isOccupied; }
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
            isOccupied = false;
        else cout << "Room is already vacant" << endl;
    }
    virtual void displayRoomInfo()
    {
        cout << "Room Number: " << roomNumber << " | Type: " << roomType << " | Is Occupied: " << (isOccupied ? "Yes" : "No") << endl;
    }
};

class ICURoom : public Room {
    const int capacity = 50;
    bool hasVentilator;
    int patientCount;
public:
    ICURoom() : Room() { hasVentilator = false; patientCount = 0; }
    ICURoom(int number, string type, bool occupied, bool ventilator) : Room(number, type, occupied)
    {
        hasVentilator = ventilator;
        patientCount = 0;
    }
    int getCapacity() { return capacity; }
    void setHasVentilator(bool ventilator) { hasVentilator = ventilator; }
    bool getHasVentilator() { return hasVentilator; }
};

class GeneralRoom : public Room {
private:
    const int capacity = 30;
    int patientCount;
public:
    GeneralRoom() : Room() { patientCount = 0; }
    GeneralRoom(int number, string type, bool occupied) : Room(number, type, occupied) { patientCount = 0; }
    int getCapacity() { return capacity; }
};

class EmergencyRoom : public Room {
private:
    const int capacity = 20;
    int patientCount;
public:
    EmergencyRoom() : Room() { patientCount = 0; }
    EmergencyRoom(int number, string type, bool occupied) : Room(number, type, occupied) { patientCount = 0; }
    int getCapacity() { return capacity; }
};

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
    void scheduleAppointment(patient& p, doctor Doctors[], int s) {
        cout << "Welcome: " << p.getcommonpersonName() << endl;
        cout << "Please book your appointment" << endl;
        cout << "Select doctor specialization: " << endl;
        cout << "1. General\n2. Surgeon\n3. Cardiologist\nChoice: ";
        int choice = getIntInput();
        string Byname = "";
        if (choice == 1) Byname = "General";
        else if (choice == 2) Byname = "Surgeon";
        else if (choice == 3) Byname = "Cardiologist";
        else { cout << "Invalid choice. Please try again." << endl; return; }
        cout << "Available Doctors for " << Byname << ":" << endl;
        for (int i = 0; i < s; i++) {
            if (toLowerStr(Doctors[i].getdoctorType()) == toLowerStr(Byname))
                cout << "  " << Doctors[i].getcommonpersonName() << "  " << Doctors[i].getdoctorStatus() << " " << Doctors[i].getdoctorType() << " " << endl;
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
            if (toLowerStr(Doctors[i].getcommonpersonName()) == toLowerStr(name))
            {
                if (Doctors[i].getdoctorStatus() == "free")
                {
                    Doctors[i].setdoctorStatus("busy");
                    Doctors[i].setappointmentStatus(true);
                    if (Doctors[i].getappdetailptr() == NULL)
                        Doctors[i].setappdetailptr(new appointmentDetail());
                    Doctors[i].setappointmentbyName(p.getcommonpersonName());
                    Doctors[i].setappointmentbyId(p.getcommonpersonID());
                    Doctors[i].setappointmenttoName(Doctors[i].getcommonpersonName());
                    Doctors[i].setappointmenttoId(Doctors[i].getcommonpersonID());
                    Doctors[i].setappointmentDay(day);
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
            cout << "No appointment has been booked yet." << endl;
    }
    bool scheduleAppointmentGUI(patient& p, doctor Doctors[], int s, string docName, string day)
    {
        currentPatient = &p;
        for (int i = 0; i < s; i++) {
            if (toLowerStr(Doctors[i].getcommonpersonName()) == toLowerStr(docName))
            {
                if (Doctors[i].getdoctorStatus() == "free")
                {
                    Doctors[i].setdoctorStatus("busy");
                    Doctors[i].setappointmentStatus(true);
                    if (Doctors[i].getappdetailptr() == NULL)
                        Doctors[i].setappdetailptr(new appointmentDetail());
                    Doctors[i].setappointmentbyName(p.getcommonpersonName());
                    Doctors[i].setappointmentbyId(p.getcommonpersonID());
                    Doctors[i].setappointmenttoName(Doctors[i].getcommonpersonName());
                    Doctors[i].setappointmenttoId(Doctors[i].getcommonpersonID());
                    Doctors[i].setappointmentDay(day);
                    this->selectedDoctor = &Doctors[i];
                    this->ifBooked = true;
                    this->doctorSpecialization = Doctors[i].getdoctorType();
                    return true;
                }
                else
                    return false;
            }
        }
        return false;
    }
    string getAppointmentInfo()
    {
        if (ifBooked && selectedDoctor != NULL && currentPatient != NULL)
        {
            string info = "";
            info += "Patient: " + currentPatient->getcommonpersonName() + "\n";
            info += "Doctor: " + selectedDoctor->getcommonpersonName() + "\n";
            info += "Specialization: " + doctorSpecialization + "\n";
            info += "Status: Confirmed\n";
            return info;
        }
        return "No appointment has been booked yet.";
    }
    doctor* getSelectedDoctor() { return selectedDoctor; }
};

class Pmedicine {
    string name;
    string type;
    int quantity;
    float price;
public:
    Pmedicine() { name = ""; type = ""; quantity = 0; price = 0.0; }
    Pmedicine(string n, string t, int q, float p) { name = n; type = t; quantity = q; price = p; }
    void setName(string n) { name = n; }
    void setType(string t) { type = t; }
    void setQuantity(int q) { if (q >= 0) quantity = q; }
    void setPrice(float p) { price = p; }
    string getName() { return name; }
    string getType() { return type; }
    int getQuantity() { return quantity; }
    float getPrice() { return price; }
    bool isQuantityEnough(int requiredQ) { return quantity >= requiredQ; }
    void reduceStock(int q) { if (q <= quantity) quantity -= q; else quantity = 0; }
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
    ReorderRequest() { name = ""; type = ""; quantityNeeded = 0; }
    ReorderRequest(string n, string t, int q) { name = n; type = t; quantityNeeded = q; }
    void setData(string n, string t, int q) { name = n; type = t; quantityNeeded = q; }
    void display() { cout << "Reordering " << name << " of Type " << type << " and Qty: " << quantityNeeded << endl; }
    string getName() { return name; }
    string getType() { return type; }
    int getQuantity() { return quantityNeeded; }
};

class Pharmacy {
private:
    Pmedicine* inventory;
    int medCount;
    const int MAX_MEDICINES = 200;
    Pmedicine* purchased;
    int purchasedCount;
    const int MAX_PURCHASES = 100;
    ReorderRequest* requests;
    int requestCount;
    const int MAX_REORDERS = 50;

public:
    Pharmacy() {
        medCount = 0;
        purchasedCount = 0;
        requestCount = 0;
        inventory = nullptr;
        purchased = nullptr;
        requests = nullptr;
    }
    ~Pharmacy() {
        if (inventory != nullptr) delete[] inventory;
        if (purchased != nullptr) delete[] purchased;
        if (requests != nullptr) delete[] requests;
    }
    Pmedicine* getPurchasedList() { return purchased; }
    int getPurchasedCount() { return purchasedCount; }
    void clearPurchasedCart() {
        if (purchased != nullptr) { delete[] purchased; purchased = nullptr; }
        purchasedCount = 0;
    }
    void addMedicine(Pmedicine m) {
        if (medCount >= MAX_MEDICINES) { cout << "Pharmacy inventory is at full capacity." << endl; return; }
        Pmedicine* newInv = new Pmedicine[medCount + 1];
        for (int i = 0; i < medCount; i++) newInv[i] = inventory[i];
        newInv[medCount] = m;
        if (inventory != nullptr) delete[] inventory;
        inventory = newInv;
        medCount++;
    }
    int findMedicine(string name) {
        for (int i = 0; i < medCount; i++) {
            if (toLowerStr(inventory[i].getName()) == toLowerStr(name)) return i;
        }
        return -1;
    }
    bool isAvailable(string name) { return findMedicine(name) != -1; }
    void addStock(int index, int qty) {
        int cur = inventory[index].getQuantity();
        inventory[index].setQuantity(cur + qty);
        saveToFile("medicine.txt");
    }
    void sendReorder(string name, string type, int qty) {
        if (requestCount >= MAX_REORDERS) { cout << "Reorder list is at full capacity." << endl; return; }
        ReorderRequest* newReq = new ReorderRequest[requestCount + 1];
        for (int i = 0; i < requestCount; i++) newReq[i] = requests[i];
        newReq[requestCount].setData(name, type, qty);
        if (requests != nullptr) delete[] requests;
        requests = newReq;
        requestCount++;
        ofstream outfile("reorders.txt", ios::app);
        outfile << name << "," << type << "," << qty << endl;
        outfile.close();
    }
    void addPurchased(Pmedicine m, int qty) {
        if (purchasedCount >= MAX_PURCHASES) { cout << "Purchase cart is full!" << endl; return; }
        Pmedicine* newPurch = new Pmedicine[purchasedCount + 1];
        for (int i = 0; i < purchasedCount; i++) newPurch[i] = purchased[i];
        newPurch[purchasedCount] = m;
        newPurch[purchasedCount].setQuantity(qty);
        if (purchased != nullptr) delete[] purchased;
        purchased = newPurch;
        purchasedCount++;
    }
    void presProcess(prescription& p) {
        for (int i = 0; i < p.getCount(); i++)
        {
            string n = p.getMedicine(i).getmedicineName();
            int reqQty = p.getMedicine(i).getmedicineQuantity();
            int index = findMedicine(n);
            if (index == -1) { sendReorder(n, "unknown", reqQty); continue; }
            if (inventory[index].isQuantityEnough(reqQty)) {
                inventory[index].reduceStock(reqQty);
                addPurchased(inventory[index], reqQty);
            }
            else {
                int available = inventory[index].getQuantity();
                if (available > 0) {
                    addPurchased(inventory[index], available);
                    inventory[index].reduceStock(available);
                    sendReorder(n, inventory[index].getType(), reqQty - available);
                }
                else
                    sendReorder(n, inventory[index].getType(), reqQty);
            }
        }
        saveToFile("medicine.txt");
    }
    void showInventory() {
        for (int i = 0; i < medCount; i++)
            cout << inventory[i].getName() << " - Type: " << inventory[i].getType() << " - Stock: " << inventory[i].getQuantity() << " - Price: Rs " << inventory[i].getPrice() << endl;
    }
    void showReorders() {
        for (int i = 0; i < requestCount; i++) requests[i].display();
        if (requestCount == 0) cout << "No pending reorder requests." << endl;
    }
    void loadFromFile(string filename) {
        ifstream infile(filename);
        if (!infile) { return; }
        string line;
        while (getline(infile, line)) {
            int x;
            x = line.find(',');
            string name = stripCR(line.substr(0, x));
            line = line.substr(x + 1);
            x = line.find(',');
            string type = stripCR(line.substr(0, x));
            line = line.substr(x + 1);
            x = line.find(',');
            int quantity = stoi(line.substr(0, x));
            line = line.substr(x + 1);
            float price = stof(stripCR(line));
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
    int getMedCount() { return medCount; }
    Pmedicine getMedAt(int i) { return inventory[i]; }
};

#endif
