#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// strips trailing carriage return from strings parsed on Windows-format files
string stripCR(string s)
{
    if (!s.empty() && s[s.size() - 1] == '\r')
        s.erase(s.size() - 1);
    return s;
}

// appointnment details class 
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

// health record class 
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

// base person class
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

    // copy constructor to safely copy person details
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

// patient class
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

    // displays all basic info and health history
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

// admin class 
class admin : public common_person
{
    string checkSuggestion;
    string checkComplain;
};

// doctor class
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

    // copy constructor handles deep copy of appointment details
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
        appdetailPtr->setappointmentbyName(name);
    }
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
        return appdetailPtr;
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

// medicine class
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

// precription class 
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

    // dynamically allocates array for required number of medicines
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

    // helper function to populate medicine array data via user input
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

    // writes prescription details to file to keep a permanent record
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

// room class
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

// room type
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

// room type
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

// room type
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

// appointment scheduling class
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

    // function updated to use aggregation
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

    // appointment booking logic
    // sets doctor status to busy and points local selectedDoctor variable to the array index
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
        {
            cout << "No appointment has been booked yet." << endl;
        }
    }
    doctor* getSelectedDoctor() {
        return selectedDoctor;
    }
};

// pharmacy medicine object
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

// medicine reorder request system
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

// forward declaration to allow friend class access
class Pharmacy;
void patientPortal(doctor* Doctors, int docSize, patient* Patients, int patSize, Pharmacy& pharm, appointmentScheduling& scheduler, int& unreadFeedback);

// core pharmacy system
// updated to enforce static capacity limits on dynamically sized arrays
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

    friend void patientPortal(doctor* Doctors, int docSize, patient* Patients, int patSize, Pharmacy& pharm, appointmentScheduling& scheduler, int& unreadFeedback);

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

    Pmedicine* getPurchasedList() {
        return purchased;
    }

    int getPurchasedCount() {
        return purchasedCount;
    }

    void clearPurchasedCart() {
        if (purchased != nullptr) {
            delete[] purchased;
            purchased = nullptr;
        }
        purchasedCount = 0;
    }

    void addMedicine(Pmedicine m) {
        if (medCount >= MAX_MEDICINES) {
            cout << "Pharmacy inventory is at full capacity (" << MAX_MEDICINES << ")." << endl;
            return;
        }
        Pmedicine* newInv = new Pmedicine[medCount + 1];
        for (int i = 0; i < medCount; i++) {
            newInv[i] = inventory[i];
        }
        newInv[medCount] = m;
        if (inventory != nullptr) delete[] inventory;
        inventory = newInv;
        medCount++;
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

    // appends low stock items to a separate text file dynamically 
    void sendReorder(string name, string type, int qty) {
        if (requestCount >= MAX_REORDERS) {
            cout << "Reorder list is at full capacity (" << MAX_REORDERS << ")." << endl;
            return;
        }
        ReorderRequest* newReq = new ReorderRequest[requestCount + 1];
        for (int i = 0; i < requestCount; i++) {
            newReq[i] = requests[i];
        }
        newReq[requestCount].setData(name, type, qty);
        if (requests != nullptr) delete[] requests;
        requests = newReq;
        requestCount++;

        ofstream outfile("reorders.txt", ios::app);
        outfile << name << "," << type << "," << qty << endl;
        outfile.close();
    }

    // helper function to resize and append to purchased tracking array
    void addPurchased(Pmedicine m, int qty) {
        if (purchasedCount >= MAX_PURCHASES) {
            cout << "Purchase cart is full!" << endl;
            return;
        }
        Pmedicine* newPurch = new Pmedicine[purchasedCount + 1];
        for (int i = 0; i < purchasedCount; i++) {
            newPurch[i] = purchased[i];
        }
        newPurch[purchasedCount] = m;
        newPurch[purchasedCount].setQuantity(qty);
        if (purchased != nullptr) delete[] purchased;
        purchased = newPurch;
        purchasedCount++;
    }

    // prescription processing logic
    // checks requested medicine quantities against current inventory
    // dynamically scales arrays upward avoiding pre-allocated gaps
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
                inventory[index].reduceStock(reqQty);
                addPurchased(inventory[index], reqQty);
            }
            else {
                int available = inventory[index].getQuantity();

                if (available > 0) {
                    cout << "Only available quantity is " << available << endl;
                    addPurchased(inventory[index], available);
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

    // parsing logic for loading medicines from file
    // string.find locates comma delimiters
    // string.substr extracts the exact word up to that comma
    // stoi and stof typecast the extracted strings
    void loadFromFile(string filename) {
        ifstream infile(filename);
        if (!infile) {
            cout << "Error file cant be open" << endl;
            return;
        }

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
};

// calculates costs of assigned doctor and purchased medicines
void generateFinalBill(doctor* assignedDoctor, Pmedicine* meds, int numMeds)
{
    int totalBill = 0;

    cout << "\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";

    cout << "              PATIENT RECEIPT              \n";

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

// array resizing and file saving logic
// checks if size meets capacity bounds, dynamically allocates new larger array +1
// copies old data to new array and deletes old pointer memory
void addDoctor(doctor*& Doctors, int& s, const int MAX_DOCS) {
    if (s >= MAX_DOCS) {
        cout << "Error: Hospital has reached maximum doctor capacity (" << MAX_DOCS << ")." << endl;
        return;
    }
    doctor* newArr = new doctor[s + 1];
    for (int i = 0; i < s; i++) {
        newArr[i] = Doctors[i];
    }

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
    newArr[s] = doctor(id, name, age, type, status, fee, salary, false, NULL);

    if (Doctors != nullptr) delete[] Doctors;
    Doctors = newArr;
    s++;

    ofstream outFile("Doctor.txt", ios::app);
    if (!outFile) {
        cout << "Error opening file." << endl;
        return;
    }
    outFile << name << "," << id << "," << age << "," << status << "," << type << "," << fee << "," << salary << endl;
    outFile.close();
}

// displays all doctors and calculates ratings dynamically
void viewDoctors(doctor Doctors[], int s)
{
    cout << "List of Doctors:" << endl;
    for (int i = 0; i < s; i++) {
        string dName = Doctors[i].getcommonpersonName();
        int totalRating = 0;
        int count = 0;
        ifstream revFile("doctor_reviews.txt");
        string line;

        // calculates avg rating directly from file on view
        if (revFile) {
            while (getline(revFile, line)) {
                int pos = line.find(',');
                if (pos != string::npos && stripCR(line.substr(0, pos)) == dName) {
                    string rest = line.substr(pos + 1);
                    int pos2 = rest.find(',');
                    if (pos2 != string::npos) {
                        totalRating += stoi(stripCR(rest.substr(0, pos2)));
                        count++;
                    }
                }
            }
            revFile.close();
        }

        double avg = count > 0 ? (double)totalRating / count : 0.0;
        string ratingStr = count > 0 ? to_string(avg).substr(0, 3) : "No ratings";

        cout << "Name: " << dName
            << "  Specialization: " << Doctors[i].getdoctorType()
            << " Status: " << Doctors[i].getdoctorStatus()
            << " Avg Rating: " << ratingStr << " (" << count << " reviews)" << endl;
    }
}

// view specified doctor reviews from text file
void viewDoctorReviews() {
    cout << "Enter doctor name to view reviews: ";
    string name;
    cin >> name;
    ifstream revFile("doctor_reviews.txt");
    string line;
    bool found = false;
    if (revFile) {
        cout << "--- Reviews for Dr. " << name << " ---" << endl;
        while (getline(revFile, line)) {
            int pos = line.find(',');
            if (pos != string::npos) {
                string dName = line.substr(0, pos);
                if (dName == name) {
                    found = true;
                    string rest = line.substr(pos + 1);
                    int pos2 = rest.find(',');
                    string rating = rest.substr(0, pos2);
                    string review = rest.substr(pos2 + 1);
                    cout << "Rating: " << rating << "/5 | Review: " << review << endl;
                }
            }
        }
        revFile.close();
    }
    if (!found) cout << "No reviews found for this doctor." << endl;
}

// submit new review and rating 
void rateDoctor() {
    cout << "Enter doctor name to rate: ";
    string name;
    cin >> name;
    cout << "Enter rating (1 to 5): ";
    int rating;
    cin >> rating;
    if (rating < 1 || rating > 5)
    {
        cout << "Invalid rating. Please enter a value between 1 and 5." << endl;
        return;
    }
    cout << "Enter your review: ";
    string review;
    cin.ignore();
    getline(cin, review);

    ofstream revFile("doctor_reviews.txt", ios::app);
    if (revFile) {
        revFile << name << "," << rating << "," << review << endl;
        revFile.close();
        cout << "Thank you! Rating submitted successfully." << endl;
    }
}

// removes a doctor from the system array
void removeDoctor(doctor*& Doctors, int& s) {
    cout << "Enter doctor ID to remove: ";
    string id;
    cin >> id;
    for (int i = 0; i < s; i++) {
        if (Doctors[i].getcommonpersonID() == id) {
            for (int j = i; j < s - 1; j++) {
                Doctors[j] = Doctors[j + 1];
            }
            s--;

            // Reallocating downwards dynamically
            doctor* newArr = nullptr;
            if (s > 0) {
                newArr = new doctor[s];
                for (int k = 0; k < s; k++) {
                    newArr[k] = Doctors[k];
                }
            }
            delete[] Doctors;
            Doctors = newArr;

            ofstream outFile("Doctor.txt");
            if (outFile) {
                for (int k = 0; k < s; k++) {
                    outFile << Doctors[k].getcommonpersonName() << "," << Doctors[k].getcommonpersonID() << "," << Doctors[k].getcommonpersonAge() << "," << Doctors[k].getdoctorStatus() << "," << Doctors[k].getdoctorType() << "," << Doctors[k].getdoctorFee() << "," << Doctors[k].getdoctorSalary() << endl;
                }
                outFile.close();
            }
            cout << "Doctor removed successfully." << endl;
            return;
        }
    }
    cout << "Doctor not found." << endl;
}

// shows patient list
void seePatientDetails(patient Patients[], int s) {
    cout << "List of Patients:" << endl;
    for (int i = 0; i < s; i++) {
        cout << "Name: " << Patients[i].getcommonpersonName() << "  Age: " << Patients[i].getcommonpersonAge() << " Type: " << Patients[i].getpatientType() << endl;
    }
}

// displays room occupancy status
void seeRoomDetails(Room** rooms, int s) {
    cout << "List of Rooms:" << endl;
    if (s == 0) cout << "No rooms currently allocated." << endl;
    for (int i = 0; i < s; i++) {
        rooms[i]->displayRoomInfo();
        cout << endl;
    }
}

// prints active appointment
void seeAppointmentDetails(appointmentScheduling& scheduler) {
    cout << "Appointment Details:" << endl;
    scheduler.successfulAppointment();
}

// modifies patient data
void editPatientDetails(patient Patients[], int& s) {
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

// modify doctor data
void editDoctorDetails(doctor Doctors[], int& s) {
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

// changes specialization
void editSpecialization(doctor Doctors[], int& s) {
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

// sets doctor status flag
void editStatus(doctor*& Doctors, int& s) {
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

// changes doctor fee
void editFee(doctor*& Doctors, int& s) {
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

// updates salary
void editSalary(doctor*& Doctors, int& s) {
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

// approves or rejects leave for doctors
void manageLeaveRequests(doctor*& Doctors, int& s)
{
    cout << "--- Leave Requests ---" << endl;

    bool foundRequest = false;

    for (int i = 0; i < s; i++)
    {
        if (Doctors[i].getdoctorStatus() == "leave_requested")
        {
            foundRequest = true;

            cout << "Dr. " << Doctors[i].getcommonpersonName() << " has applied for leave." << endl;

            cout << "1. Accept Leave" << endl;

            cout << "2. Reject Leave" << endl;

            int adminChoice;

            cin >> adminChoice;

            if (adminChoice == 1)
            {
                Doctors[i].setdoctorStatus("on leave");

                cout << "Leave request ACCEPTED." << endl;
            }

            else if (adminChoice == 2)
            {
                Doctors[i].setdoctorStatus("free");

                cout << "Leave request REJECTED." << endl;
            }

            else
            {
                cout << "Invalid input. Request skipped." << endl;
            }
        }
    }

    if (!foundRequest)
    {
        cout << "No pending leave requests." << endl;
    }
}

// loads registered users from text files and prints them
void viewSignupDetails()
{
    string dummy;

    cout << "--- Admin Signups ---" << endl;
    ifstream adminFile("AdminPasswords.txt");
    if (adminFile) {
        while (getline(adminFile, dummy)) {
            if (dummy != "") cout << dummy << endl;
        }
        adminFile.close();
    }
    else {
        cout << "No Admin records found." << endl;
    }

    cout << "--- Doctor Signups ---" << endl;
    ifstream docFile("DoctorPasswords.txt");
    if (docFile) {
        while (getline(docFile, dummy)) {
            if (dummy != "") cout << dummy << endl;
        }
        docFile.close();
    }
    else {
        cout << "No Doctor records found." << endl;
    }

    cout << "--- Patient Signups ---" << endl;
    ifstream patFile("PatientPasswords.txt");
    if (patFile) {
        while (getline(patFile, dummy)) {
            if (dummy != "") cout << dummy << endl;
        }
        patFile.close();
    }
    else {
        cout << "No Patient records found." << endl;
    }
}

// views feedback from patients
void viewFeedback()
{
    cout << "--- Patient Feedback ---" << endl;
    string dummy;
    ifstream fbFile("feedback.txt");
    if (fbFile) {
        while (getline(fbFile, dummy)) {
            cout << dummy << endl;
        }
        fbFile.close();
    }
    else {
        cout << "No feedback records found." << endl;
    }
}

// admin portal menu
void adminPortal(doctor*& Doctors, patient*& Patients, Room**& rooms, int& room_c, appointmentScheduling& scheduler, int& ds, int& ps, const int MAX_DOCS, const int MAX_PATS, int& unreadFeedback) {
    cout << "Welcome to the Admin Portal" << endl;
    if (unreadFeedback > 0) {
        cout << " NOTIFICATION: You have " << unreadFeedback << " unread patient feedbacks/complaints! " << endl;
    }
    int choice = 0;
    while (choice != 12) {
        cout << "1. Add Doctor" << endl;
        cout << "2. View Doctors" << endl;
        cout << "3. Remove Doctor" << endl;
        cout << "4. see patient details" << endl;
        cout << "5. see room details" << endl;
        cout << "6. see appointment details" << endl;
        cout << "7. edit doctor details" << endl;
        cout << "8. edit patient details" << endl;
        cout << "9. Manage Leave Requests" << endl;
        cout << "10. View Signup Details" << endl;
        cout << "11. View Feedback" << endl;
        cout << "12. exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == 1) {
            cout << "Adding a new doctor" << endl;
            addDoctor(Doctors, ds, MAX_DOCS);
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
        else if (choice == 9)
        {
            manageLeaveRequests(Doctors, ds);
        }
        else if (choice == 10)
        {
            viewSignupDetails();
        }
        else if (choice == 11)
        {
            viewFeedback();
            unreadFeedback = 0; // resets counter upon reading
        }
        else if (choice == 12)
        {
            cout << "Exiting Admin Portal" << endl;
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
        }
    } // end while
    cout << "Thank you for using the Admin Portal." << endl;
}

// view function for patient array
void viewAllpatients(patient Patients[], int s) {
    cout << "List of Patients:" << endl;
    for (int i = 0; i < s; i++) {
        cout << "Name: " << Patients[i].getcommonpersonName() << "  Age: " << Patients[i].getcommonpersonAge() << " Type: " << Patients[i].getpatientType() << endl;
    }
}

// searches patient by name and prints health record
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

// searches patient by name and prints prescription details
// updated to read from text file via string parsing
void viewPrescription(patient Patients[], int s) {
    cout << "Enter patient name to view prescription: ";
    string name;
    cin >> name;
    bool found = false;
    for (int i = 0; i < s; i++) {
        if (Patients[i].getcommonpersonName() == name) {
            cout << "Prescription for " << name << endl;
            cout << "Patient Name: " << Patients[i].getcommonpersonName() << endl;
            cout << "Patient ID: " << Patients[i].getcommonpersonID() << endl;
            cout << "Patient Age: " << Patients[i].getcommonpersonAge() << endl;
            cout << "Patient Diagnosis: " << Patients[i].getDiagnosis() << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Patient not found." << endl;
        return;
    }

    ifstream infile("prescriptions.txt");
    string line;
    bool hasMeds = false;
    if (infile) {
        cout << "--- Prescribed Medicines ---" << endl;
        while (getline(infile, line)) {
            int pos = line.find(',');
            if (pos != string::npos) {
                string pName = line.substr(0, pos);
                if (pName == name) {
                    hasMeds = true;
                    string rest = line.substr(pos + 1);
                    int p2 = rest.find(',');
                    string medName = rest.substr(0, p2);
                    rest = rest.substr(p2 + 1);
                    int p3 = rest.find(',');
                    string medType = rest.substr(0, p3);
                    rest = rest.substr(p3 + 1);
                    int p4 = rest.find(',');
                    string medQty = rest.substr(0, p4);
                    string medTime = rest.substr(p4 + 1);
                    cout << "Medicine: " << medName << " | Type: " << medType << " | Qty: " << medQty << " | Time: " << medTime << endl;
                }
            }
        }
        infile.close();
    }
    if (!hasMeds) {
        cout << "No medicines on file." << endl;
    }
}

// array resizing and file saving logic
// dynamically assigns larger array capacity when bounds are reached
// prevents memory leak by safely copying existing indices
void addPatient(patient*& Patients, int& s, const int MAX_PATS) {
    if (s >= MAX_PATS) {
        cout << "Error: Hospital has reached maximum patient capacity (" << MAX_PATS << ")." << endl;
        return;
    }
    patient* newArr = new patient[s + 1];
    for (int i = 0; i < s; i++) {
        newArr[i] = Patients[i];
    }

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
    newArr[s] = patient(id, name, age, type, symptom, diagnose);

    if (Patients != nullptr) delete[] Patients;
    Patients = newArr;
    s++;

    ofstream outFile("Patient.txt", ios::app);
    if (!outFile) {
        cout << "Error opening file." << endl;
        return;
    }
    outFile << id << "," << name << "," << age << "," << type << "," << symptom << "," << diagnose << endl;
    outFile.close();

    ofstream hrFile("health_records.txt", ios::app);
    if (hrFile)
    {
        hrFile << name << "," << symptom << "," << diagnose << endl;
        hrFile.close();
    }
}

// removes a patient from memory array
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

            patient* newArr = nullptr;
            if (s > 0) {
                newArr = new patient[s];
                for (int k = 0; k < s; k++) {
                    newArr[k] = Patients[k];
                }
            }
            delete[] Patients;
            Patients = newArr;

            cout << "Patient " << name << " removed successfully." << endl;
            return;
        }
    }
    cout << "Patient not found." << endl;
}

// leave application function for doctor
void applyLeave(doctor Doctors[], int s)
{
    cout << "Enter doctor name to apply for leave: ";

    string name;

    cin >> name;

    for (int i = 0; i < s; i++)
    {
        if (Doctors[i].getcommonpersonName() == name)
        {
            cout << "Sending leave request to Admin for Dr. " << name << endl;

            string status = "leave_requested";

            Doctors[i].setdoctorStatus(status);

            cout << "Request sent successfully! Pending Admin approval." << endl;

            return;
        }
    }

    cout << "Doctor not found." << endl;
}

// doctor sets own status
void setStatus(doctor Doctors[], int s)
{
    cout << "Enter your doctor name: ";
    string name;
    cin >> name;
    for (int i = 0; i < s; i++)
    {
        if (Doctors[i].getcommonpersonName() == name)
        {
            cout << "Enter new status (free/busy): ";
            string status;
            cin >> status;
            Doctors[i].setdoctorStatus(status);
            cout << "Status updated successfully." << endl;
            return;
        }
    }
    cout << "Doctor not found." << endl;
}

// doctor sets own fee
void setFee(doctor Doctors[], int s)
{
    cout << "Enter your doctor name: ";
    string name;
    cin >> name;
    for (int i = 0; i < s; i++)
    {
        if (Doctors[i].getcommonpersonName() == name)
        {
            cout << "Enter new fee: ";
            int fee;
            cin >> fee;
            Doctors[i].setdoctorFee(fee);
            cout << "Fee updated successfully." << endl;
            return;
        }
    }
    cout << "Doctor not found." << endl;
}

// doctor views their current appointment
void seeAppointments(appointmentScheduling& scheduler)
{
    scheduler.successfulAppointment();
}

// doctor portal menu
void doctorPortal(doctor*& Doctors, patient*& Patients, Room**& rooms, int& room_c, appointmentScheduling& scheduler, int& doc_s, int& pat_s, const int MAX_DOCS, const int MAX_PATS, const int MAX_ROOMS) {
    cout << "Welcome to the Doctor Portal" << endl;
    int choice = 0;
    while (choice != 12) {
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
        cout << "10. Admit Patient to Room" << endl;
        cout << "11. Release Room" << endl;
        cout << "12. exit " << endl;
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
            addPatient(Patients, pat_s, MAX_PATS);
            break;
        case 8:
            removePatient(Patients, pat_s);
            break;
        case 9:
            applyLeave(Doctors, doc_s);
            break;
        case 10:
        {
            if (room_c >= MAX_ROOMS) {
                cout << "Error: Hospital is at full capacity (" << MAX_ROOMS << " rooms). Cannot admit more patients untill the rooms are cleared." << endl;
            }
            else {
                Room** newRooms = new Room * [room_c + 1];
                for (int i = 0; i < room_c; i++) {
                    newRooms[i] = rooms[i];
                }
                newRooms[room_c] = new GeneralRoom(room_c + 1, "General", true);
                if (rooms != nullptr) {
                    delete[] rooms;
                }
                rooms = newRooms;
                room_c++;
                cout << "Patient successfully admitted to Room " << room_c << "." << endl;
            }
        }
        break;
        case 11:
        {
            cout << "Enter room number to release: ";
            int rNum;
            cin >> rNum;
            bool found = false;
            for (int i = 0; i < room_c; i++) {
                if (rooms[i]->getNumber() == rNum) {
                    found = true;
                    rooms[i]->releaseRoom();
                    delete rooms[i];

                    Room** newRooms = nullptr;
                    if (room_c - 1 > 0) {
                        newRooms = new Room * [room_c - 1];
                        int idx = 0;
                        for (int j = 0; j < room_c; j++) {
                            if (j != i) {
                                newRooms[idx++] = rooms[j];
                            }
                        }
                    }
                    delete[] rooms;
                    rooms = newRooms;
                    room_c--;
                    cout << "Room " << rNum << " cleared and deallocated." << endl;
                    break;
                }
            }
            if (!found) cout << "Room not found." << endl;
        }
        break;
        default:
            if (choice != 12) cout << "Invalid choice. Please try again." << endl;
        }
    }
    cout << "Thank you for visiting..." << endl;
}

// patient portal menu 
void patientPortal(doctor* Doctors, int docSize, patient* Patients, int patSize, Pharmacy& pharm, appointmentScheduling& scheduler, int& unreadFeedback)
{
    int choice = 0;
    while (choice != 8)
    {
        cout << "----------------Welcome To The Patient Portal----------------------" << endl;
        cout << "Press key to perform task " << endl;
        cout << "1. View all Doctors" << endl;
        cout << "2. Book an appointment" << endl;
        cout << "3. View Health Record" << endl;
        cout << "4. View Prescription" << endl;
        cout << "5. Buy Medicine" << endl;
        cout << "6. Fill a complain" << endl;
        cout << "7. Fill a suggestion" << endl;
        cout << "8. Exit" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            viewDoctors(Doctors, docSize);
            cout << "\n1. Read Doctor Reviews\n2. Rate a Doctor\n3. Go Back\nChoice: ";
            int subChoice;
            cin >> subChoice;
            if (subChoice == 1) {
                viewDoctorReviews();
            }
            else if (subChoice == 2) {
                rateDoctor();
            }
        }
        break;
        case 2:
        {
            cout << "Enter your patient name to book appointment: ";
            string pName;
            cin >> pName;
            bool found = false;
            for (int i = 0; i < patSize; i++) {
                if (Patients[i].getcommonpersonName() == pName) {
                    scheduler.scheduleAppointment(Patients[i], Doctors, docSize);
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Patient not found. Please register first." << endl;
        }
        break;
        case 3:
            viewHealthRecord(Patients, patSize);
            break;
        case 4:
            viewPrescription(Patients, patSize);
            break;
        case 5:
            cout << "Available Inventory:\n";

            pharm.showInventory();

            int medAmount;

            cout << "Enter number of different medicines to buy (0 to skip to bill): ";

            cin >> medAmount;

            if (medAmount > 0)
            {
                cout << "Enter your patient name for the prescription record: ";
                string pName;
                cin >> pName;

                patient dummyPatient;
                dummyPatient.setcommonpersonName(pName);

                prescription selfPrescription(nullptr, dummyPatient, medAmount);

                pharm.presProcess(selfPrescription);

                selfPrescription.saveToFile("prescriptions.txt");
            }

            if (scheduler.getSelectedDoctor() != nullptr)
            {
                generateFinalBill(scheduler.getSelectedDoctor(), pharm.purchased, pharm.purchasedCount);
            }

            else
            {
                generateFinalBill(nullptr, pharm.purchased, pharm.purchasedCount);
            }

            break;
        case 6:
        {
            cout << "Enter your complaint: ";
            string comp;
            cin.ignore();
            getline(cin, comp);
            ofstream fb("feedback.txt", ios::app);
            if (fb) {
                fb << "Complaint: " << comp << endl;
                fb.close();
                unreadFeedback++;
                cout << "Complaint submitted." << endl;
            }
        }
        break;
        case 7:
        {
            cout << "Enter your suggestion: ";
            string sugg;
            cin.ignore();
            getline(cin, sugg);
            ofstream fb("feedback.txt", ios::app);
            if (fb) {
                fb << "Suggestion: " << sugg << endl;
                fb.close();
                unreadFeedback++;
                cout << "Suggestion submitted." << endl;
            }
        }
        break;
        default:
            if (choice != 8) cout << "Invalid choice. Please try again." << endl;
        }
    }

    cout << "Thank you for visiting..." << endl;
}

// password size verification
bool passwordChecker(string pass)
{
    if (pass.length() <= 10)
    {
        return true;
    }
    else
        return false;
}

// id size verification
bool idsizeChecker(string id)
{
    if (id.length() == 4)
        return true;
    else
        return false;
}

// checks text file for unique id
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
            if (!fileID.empty() && fileID[fileID.size() - 1] == '\r')
                fileID.erase(fileID.size() - 1);
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

// portal signup and login logic
// traverses password files for string match before allowing access
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
                    // strip Windows carriage return if present
                    if (!filePass.empty() && filePass[filePass.size() - 1] == '\r')
                        filePass.erase(filePass.size() - 1);
                    if (!fileID.empty() && fileID[fileID.size() - 1] == '\r')
                        fileID.erase(fileID.size() - 1);
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
                        cout << "User added successfully" << endl;
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

// populates the system arrays with data from text files at startup
// parses strings using find(',') and substr() to locate variables
// converts numeric strings via stoi before instantiating objects
void bootup(doctor*& docPtr, patient*& patPtr, int& docSize, int& patSize, Pharmacy& pharm)
{
    pharm.loadFromFile("medicine.txt");

    // verifying new files added in step 5 and 6
    ifstream presCheck("prescriptions.txt");
    if (!presCheck) {
        ofstream makePres("prescriptions.txt");
        makePres.close();
    }
    else {
        presCheck.close();
    }

    ifstream hrCheck("health_records.txt");
    if (!hrCheck) {
        ofstream makeHr("health_records.txt");
        makeHr.close();
    }
    else {
        hrCheck.close();
    }

    // creating review file logic if empty
    ifstream revCheck("doctor_reviews.txt");
    if (!revCheck) {
        ofstream makeRev("doctor_reviews.txt");
        makeRev.close();
    }
    else {
        revCheck.close();
    }

    int loopController = 0;
    string dummy;
    ifstream infilecountingdoc("Doctor.txt");
    if (!infilecountingdoc)
    {
        cout << "Cannot open file" << endl;
    }
    while (getline(infilecountingdoc, dummy))
    {
        docSize++;
    }
    infilecountingdoc.close();
    if (docSize > 0) docPtr = new doctor[docSize];
    else docPtr = nullptr;

    ifstream infilecountingpatient("Patient.txt");
    if (!infilecountingpatient)
    {
        cout << "Cannot open file" << endl;
    }
    while (getline(infilecountingpatient, dummy))
    {
        patSize++;
    }
    infilecountingpatient.close();
    if (patSize > 0) patPtr = new patient[patSize];
    else patPtr = nullptr;

    // doctor loading logic
    ifstream doctorfile("Doctor.txt");
    if (!doctorfile)
    {
        cout << "Cannot open file" << endl;
    }
    while (getline(doctorfile, dummy) && loopController < docSize)
    {
        int pos;
        pos = dummy.find(',');
        string name = stripCR(dummy.substr(0, pos));
        dummy = dummy.substr(pos + 1);
        pos = dummy.find(',');
        string id = stripCR(dummy.substr(0, pos));
        dummy = dummy.substr(pos + 1);
        pos = dummy.find(',');
        int age = stoi(dummy.substr(0, pos));
        dummy = dummy.substr(pos + 1);
        pos = dummy.find(',');
        string status = stripCR(dummy.substr(0, pos));
        dummy = dummy.substr(pos + 1);
        pos = dummy.find(',');
        string type = stripCR(dummy.substr(0, pos));
        dummy = dummy.substr(pos + 1);
        pos = dummy.find(',');
        int fee = (int)stof(dummy.substr(0, pos));
        dummy = dummy.substr(pos + 1);
        int salary = (int)stof(stripCR(dummy));
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

    // patient loading logic
    ifstream patientfile("Patient.txt");
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
        string id = stripCR(dummy.substr(0, pos));
        dummy = dummy.substr(pos + 1);
        pos = dummy.find(',');
        string name = stripCR(dummy.substr(0, pos));
        dummy = dummy.substr(pos + 1);
        pos = dummy.find(',');
        int age = stoi(dummy.substr(0, pos));
        dummy = dummy.substr(pos + 1);
        pos = dummy.find(',');
        string type = stripCR(dummy.substr(0, pos));
        dummy = dummy.substr(pos + 1);
        pos = dummy.find(',');
        string symptom = stripCR(dummy.substr(0, pos));
        dummy = dummy.substr(pos + 1);
        string diagnosis = stripCR(dummy);
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

// main 
int main()
{
    doctor* doctorPtr = nullptr;
    patient* patientPtr = nullptr;

    int doctorSize = 0;
    int patientSize = 0;

    // Static upperbound constraints passed structurally
    const int MAX_DOCTORS = 100;
    const int MAX_PATIENTS = 500;
    const int MAX_HOSPITAL_ROOMS = 100;

    Room** rooms = nullptr;
    int roomCount = 0;

    // Notification flag counter for the admin portal
    int unreadFeedback = 0;

    Pharmacy pharm;
    appointmentScheduling scheduler;

    bool registrationVerifier = false;

    // Bootup is called; pointers are instantiated perfectly to size found on disk. 
    // No wasted array blocks.
    bootup(doctorPtr, patientPtr, doctorSize, patientSize, pharm);

    cout << "-----Welcome to the Hospital Management System------" << endl;
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
                adminPortal(doctorPtr, patientPtr, rooms, roomCount, scheduler, doctorSize, patientSize, MAX_DOCTORS, MAX_PATIENTS, unreadFeedback);
            }
            else
                cout << "Registration Failed" << endl;
        }
        else if (choice == 2)
        {
            registrationVerifier = registrationportal("Doctor", "DoctorPasswords.txt");
            if (registrationVerifier)
            {
                doctorPortal(doctorPtr, patientPtr, rooms, roomCount, scheduler, doctorSize, patientSize, MAX_DOCTORS, MAX_PATIENTS, MAX_HOSPITAL_ROOMS);
            }
            else
                cout << "Registration Failed" << endl;

        }
        else if (choice == 3)
        {
            registrationVerifier = registrationportal("Patient", "PatientPasswords.txt");
            if (registrationVerifier)
            {
                patientPortal(doctorPtr, doctorSize, patientPtr, patientSize, pharm, scheduler, unreadFeedback);
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
    if (rooms != nullptr)
    {
        for (int i = 0; i < roomCount; i++)
        {
            delete rooms[i];
        }
        delete[] rooms;
    }

    return 0;
}