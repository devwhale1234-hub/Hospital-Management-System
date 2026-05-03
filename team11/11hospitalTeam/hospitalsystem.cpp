#include "hospitalsystem.h"
#include <fstream>
#include <sstream>

doctor*   HospitalSystem::Doctors      = nullptr;
patient*  HospitalSystem::Patients     = nullptr;
Room**    HospitalSystem::rooms        = nullptr;
Pharmacy  HospitalSystem::pharm;
appointmentScheduling HospitalSystem::scheduler;
int HospitalSystem::docSize       = 0;
int HospitalSystem::patSize       = 0;
int HospitalSystem::roomCount     = 0;
int HospitalSystem::unreadFeedback = 0;

void HospitalSystem::bootup()
{
    pharm.loadFromFile("medicine.txt");

    roomCount = 100;
    rooms = new Room*[roomCount];
    for (int i = 0;  i < 30;  i++) rooms[i]  = new GeneralRoom(i + 1,  "General",   false);
    for (int i = 30; i < 80;  i++) rooms[i]  = new ICURoom(i + 1,       "ICU",       false, false);
    for (int i = 80; i < 100; i++) rooms[i]  = new EmergencyRoom(i + 1, "Emergency", false);

    ifstream presCheck("prescriptions.txt");
    if (!presCheck) { ofstream m("prescriptions.txt"); m.close(); } else presCheck.close();
    ifstream hrCheck("health_records.txt");
    if (!hrCheck)   { ofstream m("health_records.txt"); m.close(); } else hrCheck.close();
    ifstream revCheck("doctor_reviews.txt");
    if (!revCheck)  { ofstream m("doctor_reviews.txt"); m.close(); } else revCheck.close();
    ifstream fbCheck("feedback.txt");
    if (!fbCheck)   { ofstream m("feedback.txt"); m.close(); } else fbCheck.close();

    string dummy;
    ifstream inDoc("Doctor.txt");
    if (inDoc) { while (getline(inDoc, dummy)) docSize++; inDoc.close(); }
    if (docSize > 0) Doctors = new doctor[docSize]; else Doctors = nullptr;

    ifstream inPat("Patient.txt");
    if (inPat) { while (getline(inPat, dummy)) patSize++; inPat.close(); }
    if (patSize > 0) Patients = new patient[patSize]; else Patients = nullptr;

    int lc = 0;
    ifstream doctorfile("Doctor.txt");
    if (doctorfile)
    {
        while (getline(doctorfile, dummy) && lc < docSize)
        {
            int pos;
            pos = dummy.find(','); string name = stripCR(dummy.substr(0, pos)); dummy = dummy.substr(pos + 1);
            pos = dummy.find(','); string id   = stripCR(dummy.substr(0, pos)); dummy = dummy.substr(pos + 1);
            pos = dummy.find(','); int age     = stoi(dummy.substr(0, pos));    dummy = dummy.substr(pos + 1);
            pos = dummy.find(','); string status = stripCR(dummy.substr(0, pos)); dummy = dummy.substr(pos + 1);
            pos = dummy.find(','); string type  = stripCR(dummy.substr(0, pos)); dummy = dummy.substr(pos + 1);
            pos = dummy.find(','); int fee      = (int)stof(dummy.substr(0, pos)); dummy = dummy.substr(pos + 1);
            int salary = (int)stof(stripCR(dummy));
            Doctors[lc].setcommonpersonName(name);
            Doctors[lc].setcommonpersonID(id);
            Doctors[lc].setcommonpersonAge(age);
            Doctors[lc].setdoctorType(type);
            Doctors[lc].setdoctorStatus(status);
            Doctors[lc].setdoctorFee(fee);
            Doctors[lc].setdoctorSalary(salary);
            lc++;
        }
        doctorfile.close();
    }

    lc = 0;
    ifstream patientfile("Patient.txt");
    if (patientfile)
    {
        while (getline(patientfile, dummy) && lc < patSize)
        {
            int pos;
            pos = dummy.find(','); string id    = stripCR(dummy.substr(0, pos)); dummy = dummy.substr(pos + 1);
            pos = dummy.find(','); string name  = stripCR(dummy.substr(0, pos)); dummy = dummy.substr(pos + 1);
            pos = dummy.find(','); int age      = stoi(dummy.substr(0, pos));    dummy = dummy.substr(pos + 1);
            pos = dummy.find(','); string type  = stripCR(dummy.substr(0, pos)); dummy = dummy.substr(pos + 1);
            pos = dummy.find(','); string symptom = stripCR(dummy.substr(0, pos)); dummy = dummy.substr(pos + 1);
            string diagnosis = stripCR(dummy);
            Patients[lc].setcommonpersonName(name);
            Patients[lc].setcommonpersonID(id);
            Patients[lc].setcommonpersonAge(age);
            Patients[lc].setpatientType(type);
            Patients[lc].setSymptoms(symptom);
            Patients[lc].setDiagnosis(diagnosis);
            lc++;
        }
        patientfile.close();
    }
}

bool HospitalSystem::idVerifier(string checkingID, string file)
{
    string word;
    ifstream infile(file);
    if (!infile) return true;
    while (getline(infile, word))
    {
        int pos = word.find(',');
        if (pos == (int)string::npos) continue;
        string fileID = word.substr(0, pos);
        if (!fileID.empty() && fileID[fileID.size()-1] == '\r') fileID.erase(fileID.size()-1);
        if (fileID == checkingID) { infile.close(); return false; }
    }
    infile.close();
    return true;
}

bool HospitalSystem::passwordChecker(string pass) { return pass.length() <= 10; }
bool HospitalSystem::idsizeChecker(string id) { return id.length() == 4; }

bool HospitalSystem::loginUser(string id, string pass, string file)
{
    string word;
    ifstream infile(file);
    if (!infile) return false;
    while (getline(infile, word))
    {
        int pos = word.find(',');
        if (pos == (int)string::npos) continue;
        string fileID   = word.substr(0, pos);
        string filePass = word.substr(pos + 1);
        if (!filePass.empty() && filePass[filePass.size()-1] == '\r') filePass.erase(filePass.size()-1);
        if (!fileID.empty()   && fileID[fileID.size()-1]   == '\r') fileID.erase(fileID.size()-1);
        if (fileID == id && filePass == pass) { infile.close(); return true; }
    }
    infile.close();
    return false;
}

bool HospitalSystem::signupUser(string id, string pass, string file)
{
    if (!idsizeChecker(id))      return false;
    if (!passwordChecker(pass))  return false;
    if (!idVerifier(id, file))   return false;
    ofstream outfile(file, ios::app);
    if (!outfile) return false;
    outfile << endl << id << "," << pass;
    outfile.close();
    return true;
}

doctor* HospitalSystem::findDoctorById(string id)
{
    for (int i = 0; i < docSize; i++)
        if (Doctors[i].getcommonpersonID() == id) return &Doctors[i];
    return nullptr;
}

doctor* HospitalSystem::findDoctorByName(string name)
{
    for (int i = 0; i < docSize; i++)
        if (toLowerStr(Doctors[i].getcommonpersonName()) == toLowerStr(name)) return &Doctors[i];
    return nullptr;
}

patient* HospitalSystem::findPatientByName(string name)
{
    for (int i = 0; i < patSize; i++)
        if (toLowerStr(Patients[i].getcommonpersonName()) == toLowerStr(name)) return &Patients[i];
    return nullptr;
}

void HospitalSystem::saveDoctors()
{
    ofstream outFile("Doctor.txt");
    for (int i = 0; i < docSize; i++)
        outFile << Doctors[i].getcommonpersonName() << "," << Doctors[i].getcommonpersonID() << ","
                << Doctors[i].getcommonpersonAge() << "," << Doctors[i].getdoctorStatus() << ","
                << Doctors[i].getdoctorType() << "," << Doctors[i].getdoctorFee() << ","
                << Doctors[i].getdoctorSalary() << endl;
    outFile.close();
}

void HospitalSystem::savePatients()
{
    ofstream outFile("Patient.txt");
    for (int i = 0; i < patSize; i++)
        outFile << Patients[i].getcommonpersonID() << "," << Patients[i].getcommonpersonName() << ","
                << Patients[i].getcommonpersonAge() << "," << Patients[i].getpatientType() << ","
                << Patients[i].getSymptoms() << "," << Patients[i].getDiagnosis() << endl;
    outFile.close();
}

string HospitalSystem::addDoctorToSystem(string id, string name, int age, string type, string status, int fee, int salary)
{
    if (docSize >= MAX_DOCTORS) return "Hospital has reached maximum doctor capacity.";
    doctor* newArr = new doctor[docSize + 1];
    for (int i = 0; i < docSize; i++) newArr[i] = Doctors[i];
    newArr[docSize] = doctor(id, name, age, type, status, fee, salary, false, NULL);
    if (Doctors != nullptr) delete[] Doctors;
    Doctors = newArr;
    docSize++;
    ofstream outFile("Doctor.txt", ios::app);
    outFile << name << "," << id << "," << age << "," << status << "," << type << "," << fee << "," << salary << endl;
    outFile.close();
    return "Doctor added successfully.";
}

string HospitalSystem::removeDoctorFromSystem(string id)
{
    for (int i = 0; i < docSize; i++)
    {
        if (toLowerStr(Doctors[i].getcommonpersonID()) == toLowerStr(id))
        {
            for (int j = i; j < docSize - 1; j++) Doctors[j] = Doctors[j + 1];
            docSize--;
            doctor* newArr = nullptr;
            if (docSize > 0) {
                newArr = new doctor[docSize];
                for (int k = 0; k < docSize; k++) newArr[k] = Doctors[k];
            }
            delete[] Doctors;
            Doctors = newArr;
            saveDoctors();
            return "Doctor removed successfully.";
        }
    }
    return "Doctor not found.";
}

string HospitalSystem::editDoctorSpec(string name, string type)
{
    doctor* d = findDoctorByName(name);
    if (!d) return "Doctor not found.";
    d->setdoctorType(type);
    saveDoctors();
    return "Specialization updated.";
}

string HospitalSystem::editDoctorStatus(string name, string status)
{
    doctor* d = findDoctorByName(name);
    if (!d) return "Doctor not found.";
    d->setdoctorStatus(status);
    saveDoctors();
    return "Status updated.";
}

string HospitalSystem::editDoctorFee(string name, int fee)
{
    doctor* d = findDoctorByName(name);
    if (!d) return "Doctor not found.";
    d->setdoctorFee(fee);
    saveDoctors();
    return "Fee updated.";
}

string HospitalSystem::editDoctorSalary(string name, int salary)
{
    doctor* d = findDoctorByName(name);
    if (!d) return "Doctor not found.";
    d->setdoctorSalary(salary);
    saveDoctors();
    return "Salary updated.";
}

string HospitalSystem::editDoctorAll(string name, string type, string status, int fee, int salary)
{
    doctor* d = findDoctorByName(name);
    if (!d) return "Doctor not found.";
    d->setdoctorType(type);
    d->setdoctorStatus(status);
    d->setdoctorFee(fee);
    d->setdoctorSalary(salary);
    saveDoctors();
    return "Doctor details updated.";
}

string HospitalSystem::addPatientToSystem(string id, string name, int age, string type, string symptom, string diagnose)
{
    if (patSize >= MAX_PATIENTS) return "Hospital has reached maximum patient capacity.";
    patient* newArr = new patient[patSize + 1];
    for (int i = 0; i < patSize; i++) newArr[i] = Patients[i];
    newArr[patSize] = patient(id, name, age, type, symptom, diagnose);
    if (Patients != nullptr) delete[] Patients;
    Patients = newArr;
    patSize++;
    ofstream outFile("Patient.txt", ios::app);
    outFile << id << "," << name << "," << age << "," << type << "," << symptom << "," << diagnose << endl;
    outFile.close();
    ofstream hrFile("health_records.txt", ios::app);
    hrFile << name << "," << symptom << "," << diagnose << endl;
    hrFile.close();
    return "Patient added successfully.";
}

string HospitalSystem::removePatientFromSystem(string name)
{
    for (int i = 0; i < patSize; i++)
    {
        if (toLowerStr(Patients[i].getcommonpersonName()) == toLowerStr(name))
        {
            for (int j = i; j < patSize - 1; j++) Patients[j] = Patients[j + 1];
            patSize--;
            patient* newArr = nullptr;
            if (patSize > 0) {
                newArr = new patient[patSize];
                for (int k = 0; k < patSize; k++) newArr[k] = Patients[k];
            }
            delete[] Patients;
            Patients = newArr;
            savePatients();
            return "Patient removed successfully.";
        }
    }
    return "Patient not found.";
}

string HospitalSystem::editPatientDetails(string name, int age, string type)
{
    patient* p = findPatientByName(name);
    if (!p) return "Patient not found.";
    p->setcommonpersonAge(age);
    p->setpatientType(type);
    savePatients();
    return "Patient details updated.";
}

string HospitalSystem::getHealthRecord(string name)
{
    patient* p = findPatientByName(name);
    if (!p) return "Patient not found.";
    string info = "Health Record for " + p->getcommonpersonName() + "\n";
    info += "Symptoms : " + p->getSymptoms() + "\n";
    info += "Diagnosis: " + p->getDiagnosis() + "\n";
    return info;
}

string HospitalSystem::getPrescriptionRecord(string name)
{
    patient* p = findPatientByName(name);
    if (!p) return "Patient not found.";
    string info = "Prescription for " + p->getcommonpersonName() + "\n";
    info += "ID   : " + p->getcommonpersonID() + "\n";
    info += "Age  : " + to_string(p->getcommonpersonAge()) + "\n";
    info += "Diag : " + p->getDiagnosis() + "\n\n";

    ifstream infile("prescriptions.txt");
    string line;
    bool hasMeds = false;
    if (infile)
    {
        info += "--- Prescribed Medicines ---\n";
        while (getline(infile, line))
        {
            int pos = line.find(',');
            if (pos != (int)string::npos)
            {
                string pName = line.substr(0, pos);
                if (toLowerStr(pName) == toLowerStr(name))
                {
                    hasMeds = true;
                    string rest = line.substr(pos + 1);
                    int p2 = rest.find(','); string medName = rest.substr(0, p2); rest = rest.substr(p2 + 1);
                    int p3 = rest.find(','); string medType = rest.substr(0, p3); rest = rest.substr(p3 + 1);
                    int p4 = rest.find(','); string medQty  = rest.substr(0, p4);
                    string medTime = rest.substr(p4 + 1);
                    info += "Medicine: " + medName + " | Type: " + medType + " | Qty: " + medQty + " | Time: " + stripCR(medTime) + "\n";
                }
            }
        }
        infile.close();
    }
    if (!hasMeds) info += "No medicines on file.\n";
    return info;
}

string HospitalSystem::bookAppointment(string patName, string docName, string day)
{
    patient* p = findPatientByName(patName);
    if (!p) return "Patient not found.";
    doctor* d = findDoctorByName(docName);
    if (!d) return "Doctor not found.";
    if (d->getdoctorStatus() != "free") return "Doctor " + docName + " is currently busy.";
    bool ok = scheduler.scheduleAppointmentGUI(*p, Doctors, docSize, docName, day);
    if (ok) return "Appointment booked successfully with Dr. " + docName + " on " + day + ".";
    return "Could not book appointment.";
}

string HospitalSystem::getAppointmentInfo()
{
    return scheduler.getAppointmentInfo();
}

string HospitalSystem::applyLeaveForDoctor(string docName)
{
    doctor* d = findDoctorByName(docName);
    if (!d) return "Doctor not found.";
    d->setdoctorStatus("leave_requested");
    saveDoctors();
    return "Leave request sent to Admin. Pending approval.";
}

string HospitalSystem::manageLeave(string docName, bool accept)
{
    doctor* d = findDoctorByName(docName);
    if (!d) return "Doctor not found.";
    if (accept) { d->setdoctorStatus("on leave"); saveDoctors(); return "Leave request ACCEPTED."; }
    else        { d->setdoctorStatus("free");     saveDoctors(); return "Leave request REJECTED."; }
}

string HospitalSystem::getLeaveRequests()
{
    string result = "";
    for (int i = 0; i < docSize; i++)
        if (Doctors[i].getdoctorStatus() == "leave_requested")
            result += Doctors[i].getcommonpersonName() + "\n";
    if (result.empty()) result = "No pending leave requests.";
    return result;
}

string HospitalSystem::admitToRoom(string patId, string roomType)
{
    int firstFree = -1, firstOccupied = -1;
    for (int i = 0; i < roomCount; i++)
    {
        if (rooms[i]->getType() == roomType)
        {
            if (!rooms[i]->getIsOccupied() && firstFree == -1) firstFree = i;
            if (rooms[i]->getIsOccupied()  && firstOccupied == -1) firstOccupied = i;
        }
    }
    if (firstFree != -1)
    {
        rooms[firstFree]->setIsOccupied(true);
        return "Patient admitted to " + roomType + " Room " + to_string(rooms[firstFree]->getNumber()) + ".";
    }
    return "NO_FREE_ROOM:" + to_string(firstOccupied != -1 ? rooms[firstOccupied]->getNumber() : -1) + ":" + roomType;
}

string HospitalSystem::releaseRoomNum(int roomNum)
{
    for (int i = 0; i < roomCount; i++)
    {
        if (rooms[i]->getNumber() == roomNum)
        {
            if (rooms[i]->getIsOccupied()) { rooms[i]->releaseRoom(); return "Room " + to_string(roomNum) + " released."; }
            else return "Room is already vacant.";
        }
    }
    return "Room not found.";
}

string HospitalSystem::addMedicineToPharm(string name, string type, int qty, float price)
{
    pharm.addMedicine(Pmedicine(name, type, qty, price));
    pharm.saveToFile("medicine.txt");
    return "Medicine added to inventory.";
}

string HospitalSystem::restockMedicine(string name, int qty)
{
    int idx = pharm.findMedicine(name);
    if (idx == -1) return "Medicine not found in inventory.";
    pharm.addStock(idx, qty);
    return "Restock successful.";
}

string HospitalSystem::getReorderList()
{
    ifstream f("reorders.txt");
    if (!f) return "No reorder file found.";
    string result = "", line;
    while (getline(f, line)) if (!line.empty()) result += line + "\n";
    f.close();
    if (result.empty()) return "No pending reorders.";
    return result;
}

string HospitalSystem::prescribeMedicines(doctor* doc, string patName, medicine* meds, int num)
{
    patient dummy;
    dummy.setcommonpersonName(patName);
    prescription pres(doc, dummy, meds, num);
    string notice = "";
    for (int i = 0; i < num; i++)
    {
        if (!pharm.isAvailable(meds[i].getmedicineName()))
        {
            notice += "NOTICE: " + meds[i].getmedicineName() + " is not in pharmacy. Patient must acquire externally.\n";
            pharm.sendReorder(meds[i].getmedicineName(), "Custom_Prescription", meds[i].getmedicineQuantity());
        }
    }
    pres.saveToFile("prescriptions.txt");
    return notice + "Prescription saved.";
}

string HospitalSystem::buyMedicines(string patName, medicine* meds, int num)
{
    patient dummy;
    dummy.setcommonpersonName(patName);
    prescription selfPres(nullptr, dummy, meds, num);
    pharm.presProcess(selfPres);
    selfPres.saveToFile("prescriptions.txt");
    return generateBillText();
}

string HospitalSystem::generateBillText()
{
    string bill = "";
    bill += "========================================\n";
    bill += "           PATIENT RECEIPT              \n";
    bill += "========================================\n";
    int totalBill = 0;
    doctor* assignedDoc = scheduler.getSelectedDoctor();
    if (assignedDoc != nullptr)
    {
        int fee = assignedDoc->getdoctorFee();
        bill += "Consultation Details:\n";
        bill += "  Specialization : " + assignedDoc->getdoctorType() + "\n";
        bill += "  Consultation Fee: Rs " + to_string(fee) + "\n";
        totalBill += fee;
    }
    else
        bill += "No doctor assigned. Consultation Fee: Rs 0\n";

    bill += "----------------------------------------\n";
    bill += "Pharmacy Charges:\n";
    int pharmacyTotal = 0;
    Pmedicine* purchased = pharm.getPurchasedList();
    int count = pharm.getPurchasedCount();
    if (purchased != nullptr && count > 0)
    {
        for (int i = 0; i < count; i++)
        {
            int itemTotal = (int)(purchased[i].getQuantity() * purchased[i].getPrice());
            pharmacyTotal += itemTotal;
            bill += "  " + purchased[i].getName() + " (" + purchased[i].getType() + ")\n";
            bill += "  " + to_string(purchased[i].getQuantity()) + " units @ Rs " + to_string((int)purchased[i].getPrice()) + " = Rs " + to_string(itemTotal) + "\n";
        }
    }
    else
        bill += "  No medicines purchased.\n";

    bill += "\nPharmacy Subtotal: Rs " + to_string(pharmacyTotal) + "\n";
    totalBill += pharmacyTotal;
    bill += "========================================\n";
    bill += "TOTAL: RUPEES " + to_string(totalBill) + " /-\n";
    bill += "========================================\n";
    return bill;
}

string HospitalSystem::addDoctorReview(string docName, int rating, string review, string pName, string pId)
{
    if (rating < 1 || rating > 5) return "Invalid rating. Enter 1-5.";
    ofstream revFile("doctor_reviews.txt", ios::app);
    if (!revFile) return "Could not open reviews file.";
    revFile << docName << "," << rating << "," << review << "," << pName << "," << pId << endl;
    revFile.close();
    return "Rating submitted successfully.";
}

string HospitalSystem::getDoctorReviews(string docName)
{
    ifstream revFile("doctor_reviews.txt");
    if (!revFile) return "No reviews file found.";
    string result = "--- Reviews for Dr. " + docName + " ---\n";
    string line;
    bool found = false;
    while (getline(revFile, line))
    {
        int pos = line.find(',');
        if (pos == (int)string::npos) continue;
        string dName = line.substr(0, pos);
        if (toLowerStr(dName) == toLowerStr(docName))
        {
            found = true;
            string rest = line.substr(pos + 1);
            int p2 = rest.find(','); string rating = rest.substr(0, p2); rest = rest.substr(p2 + 1);
            int p3 = rest.find(','); string review  = rest.substr(0, p3); rest = rest.substr(p3 + 1);
            int p4 = rest.find(','); string pName   = rest.substr(0, p4);
            string pId = stripCR(rest.substr(p4 + 1));
            result += "Patient: " + pName + " (ID: " + pId + ") | Rating: " + rating + "/5 | " + review + "\n";
        }
    }
    revFile.close();
    if (!found) result += "No reviews found.\n";
    return result;
}

string HospitalSystem::getDoctorAvgRating(string docName)
{
    ifstream revFile("doctor_reviews.txt");
    if (!revFile) return "No ratings";
    int total = 0, count = 0;
    string line;
    while (getline(revFile, line))
    {
        int pos = line.find(',');
        if (pos == (int)string::npos) continue;
        if (toLowerStr(stripCR(line.substr(0, pos))) == toLowerStr(docName))
        {
            string rest = line.substr(pos + 1);
            int p2 = rest.find(',');
            if (p2 != (int)string::npos) { total += stoi(rest.substr(0, p2)); count++; }
        }
    }
    revFile.close();
    if (count == 0) return "No ratings";
    double avg = (double)total / count;
    ostringstream oss;
    oss.precision(2);
    oss << avg << " (" << count << " reviews)";
    return oss.str();
}

string HospitalSystem::getSignupDetails()
{
    string result = "--- Admin Signups ---\n";
    string dummy;
    ifstream a("AdminPasswords.txt");
    if (a) { while (getline(a, dummy)) if (!dummy.empty()) result += dummy + "\n"; a.close(); }
    result += "--- Doctor Signups ---\n";
    ifstream d("DoctorPasswords.txt");
    if (d) { while (getline(d, dummy)) if (!dummy.empty()) result += dummy + "\n"; d.close(); }
    result += "--- Patient Signups ---\n";
    ifstream p("PatientPasswords.txt");
    if (p) { while (getline(p, dummy)) if (!dummy.empty()) result += dummy + "\n"; p.close(); }
    return result;
}

string HospitalSystem::getFeedbackContents()
{
    string result = "";
    string line;
    ifstream f("feedback.txt");
    if (!f) return "No feedback records found.";
    while (getline(f, line)) result += line + "\n";
    f.close();
    if (result.empty()) return "No feedback records found.";
    return result;
}

void HospitalSystem::addFeedback(string text, bool isComplaint)
{
    ofstream fb("feedback.txt", ios::app);
    if (fb)
    {
        if (isComplaint) fb << "Complaint: " << text << endl;
        else             fb << "Suggestion: " << text << endl;
        fb.close();
        unreadFeedback++;
    }
}
