#ifndef HOSPITALSYSTEM_H
#define HOSPITALSYSTEM_H

#include "hospitaldata.h"
#include <string>

class HospitalSystem
{
public:
    static doctor*   Doctors;
    static patient*  Patients;
    static Room**    rooms;
    static Pharmacy  pharm;
    static appointmentScheduling scheduler;
    static int docSize;
    static int patSize;
    static int roomCount;
    static int unreadFeedback;
    static const int MAX_DOCTORS  = 100;
    static const int MAX_PATIENTS = 500;
    static const int MAX_ROOMS    = 100;

    static void bootup();

    static bool loginUser(string id, string pass, string file);
    static bool signupUser(string id, string pass, string file);

    static doctor*  findDoctorById(string id);
    static doctor*  findDoctorByName(string name);
    static patient* findPatientByName(string name);

    static string addDoctorToSystem(string id, string name, int age, string type, string status, int fee, int salary);
    static string removeDoctorFromSystem(string id);
    static string editDoctorSpec(string name, string type);
    static string editDoctorStatus(string name, string status);
    static string editDoctorFee(string name, int fee);
    static string editDoctorSalary(string name, int salary);
    static string editDoctorAll(string name, string type, string status, int fee, int salary);
    static void   saveDoctors();

    static string addPatientToSystem(string id, string name, int age, string type, string symptom, string diagnose);
    static string removePatientFromSystem(string name);
    static string editPatientDetails(string name, int age, string type);
    static void   savePatients();

    static string getHealthRecord(string name);
    static string getPrescriptionRecord(string name);

    static string bookAppointment(string patName, string docName, string day);
    static string getAppointmentInfo();

    static string applyLeaveForDoctor(string docName);
    static string manageLeave(string docName, bool accept);
    static string getLeaveRequests();

    static string admitToRoom(string patId, string roomType);
    static string releaseRoomNum(int roomNum);

    static string addMedicineToPharm(string name, string type, int qty, float price);
    static string restockMedicine(string name, int qty);
    static string getReorderList();

    static string prescribeMedicines(doctor* doc, string patName, medicine* meds, int num);
    static string buyMedicines(string patName, medicine* meds, int num);
    static string generateBillText();

    static string addDoctorReview(string docName, int rating, string review, string pName, string pId);
    static string getDoctorReviews(string docName);
    static string getDoctorAvgRating(string docName);

    static string getSignupDetails();
    static string getFeedbackContents();
    static void   addFeedback(string text, bool isComplaint);

private:
    static bool   idVerifier(string checkingID, string file);
    static bool   passwordChecker(string pass);
    static bool   idsizeChecker(string id);
};

#endif
