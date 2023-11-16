#include<iostream> //For Input and Output
#include<string> //For String related functions
#include<fstream> //For File Handling
#include<ctime> //For Generating Unique ID with respect to time;
#include<cstdlib> //For using srand() function to generate randon number
#include<conio.h> //For getch() functionality
#include<cstdio> //For using rename() and remove() functions of file
using namespace std;

/*--- Declaration of User-Defined Functions ---*/
void welcomeMenu(); // For Welcome Menu Interface
void applyForPassport(); //For Registration Form
void adminLoginInterface(); //For Admin Login Interface
void adminPanelInterface(); //For Adimin Panel Interface
int generateID(int, int); //For Generating Unique ID for each new Applicant
string spaceToStarac(string); //To convert space into starac(*) before saving data
string staracToSpace(string); //To convert starac(*) into space after reading data

/*--- Creating class for new applicants ---*/
class NewApplicant {
	protected:
		string name, fatherName, address, dateOfBirth, placeOfBirth, gender, nationality, status;
		int age, cnic, applicationID;
	public:
		void application(); //Register Form
		void apply(); //Apply process
		friend class AdminSearch; //Creating firend class
		//Creating friend operator function
		friend ostream& operator << (ostream& print, NewApplicant& applicant);
};
void NewApplicant::application() {
	cin.ignore();
	cout<<"\n\t\t\t\t\tEnter your Full Name: ";
	getline(cin, name);
	name= spaceToStarac(name);
	cout<<"\n\t\t\t\t\tEnter your Father's Name: ";
	getline(cin, fatherName);
	fatherName= spaceToStarac(fatherName);
	cout<<"\n\t\t\t\t\tEnter Date of Birth Name(DD-MM-YY): ";
	getline(cin, dateOfBirth);
	
	int genderChoice=0;
	bool genderChoiceError= false;
	
	while(true) {
		if(genderChoiceError== true) {
			cout<<"\n\t\t\t\t\t**Error: Invalid Gender Choice!"<<endl;
		}
		
		cout<<"\n\t\t\t\t\tGender: "<<endl
		<<"\t\t\t\t\t\tPress '1' for Male"<<endl
		<<"\t\t\t\t\t\tPress '2' for Female"<<endl
		<<"\n\t\t\t\t\tEnter your Gender Choice: ";
		cin>>genderChoice;
		
		if(genderChoice==1) {
			gender= "Male";
			break;
		}
		else if(genderChoice==2) {
			gender= "Female";
			break;
		}
		else {
			genderChoiceError= true;
		}
	}
	cout<<"\n\t\t\t\t\tEnter your Age: ";
	cin>>age;
	cout<<"\n\t\t\t\t\tEnter your Birth Place: ";
	cin.ignore();
	getline(cin, placeOfBirth);
	placeOfBirth= spaceToStarac(placeOfBirth);
	cout<<"\n\t\t\t\t\tEnter your Current Address: ";
	getline(cin, address);
	address= spaceToStarac(address);
	cout<<"\n\t\t\t\t\tEnter your Nationality: ";
	getline(cin, nationality);
	cout<<"\n\t\t\t\t\tEnter your CNIC Number: ";
	cin>>cnic;
	applicationID= generateID(1000, 9999);
	status= "Pending";
	
	apply();
	
	cout<<"\n\n\t\t\t\t\t-----------------------------------------"<<endl
		<<"\t\t\t\t\t|	Your Application ID: "<<applicationID<<"	|"<<endl
		<<"\t\t\t\t\t|	You Applied Successfully!	|"<<endl
		<<"\t\t\t\t\t|	Admin will review it Shortly	|"<<endl
		<<"\t\t\t\t\t-----------------------------------------"<<endl;
		
	cout<<"\n\n\t\t\t\t\tPress any key to go to Welcome Menu";
	if(getch()) {
		system("CLS");
		welcomeMenu();
	}
}
void NewApplicant::apply() {
	
	fstream pendingFile;
	pendingFile.open("pendingFile.txt", ios::app);
	if(pendingFile.is_open()) {
		pendingFile<<applicationID<<" "<<name<<" "<<fatherName<<" "<<dateOfBirth<<" "
					<<gender<<" "<<nationality<<" "<<placeOfBirth<<" "<<cnic<<" "
					<<address<<" "<<age<<" "<<status<<endl;
		pendingFile.close();
	}
}

/*--- Creating class for user ro serach its application ---*/
class ApplicantSearch: protected NewApplicant {
	
	protected:
		int searchApplicationID;
	public:		
		ApplicantSearch();
	
};
ApplicantSearch::ApplicantSearch() {
	
	bool recordFound= false;
	// int count=1;
	string line;
	
	system("CLS");
	cout<<"\n\n\n\t\t\t\t\t-----------------------------------------"<<endl
			<<"\t\t\t\t\t|	Passport Management System	|"<<endl
			<<"\t\t\t\t\t-----------------------------------------"<<endl
			<<"\t\t\t\t\t|	 Search by Application ID	|"<<endl
			<<"\t\t\t\t\t-----------------------------------------"<<endl;
	
	cout<<"\n\t\t\t\t\tEnter Application ID: ";
	cin>>searchApplicationID;
	
	fstream pending;
	pending.open("pendingFile.txt", ios::in);

	while(pending>>applicationID>>name>>fatherName>>dateOfBirth>>gender>>nationality>>placeOfBirth>>cnic>>address>>age>>status) {
		if(searchApplicationID==applicationID) {
			recordFound= true;
			break;
		}
	}

	pending.close();

	if(recordFound== true) {
		name= staracToSpace(name);
		fatherName= staracToSpace(fatherName);
		placeOfBirth= staracToSpace(placeOfBirth);
		address= staracToSpace(address);
		dateOfBirth= staracToSpace(dateOfBirth);
		
		system("CLS");
		
		cout<<"\n\n\n\t\t\t\t\t-----------------------------------------"<<endl
			<<"\t\t\t\t\t|	Passport Management System	|"<<endl
			<<"\t\t\t\t\t-----------------------------------------"<<endl
			<<"\t\t\t\t\t|		Record Found		|"<<endl
			<<"\t\t\t\t\t|					|"<<endl;
			
		cout<<"\t\t\t\t\t| Applicant ID: "<<applicationID<<"			|"<<endl
			<<"\t\t\t\t\t| Name: "<<name<<"			|"<<endl
			<<"\t\t\t\t\t| Father's Name: "<<fatherName<<"		|"<<endl
			<<"\t\t\t\t\t| Date of Birth (DDMMYY): "<<dateOfBirth<<"	|"<<endl
			<<"\t\t\t\t\t| Age: "<<age<<"				|"<<endl
			<<"\t\t\t\t\t| Gender: "<<gender<<"				|"<<endl
			<<"\t\t\t\t\t| Birth Place: "<<placeOfBirth<<"	|"<<endl
			<<"\t\t\t\t\t| Nationality: "<<nationality<<"		|"<<endl
			<<"\t\t\t\t\t| CNIC: "<<cnic<<"			|"<<endl
			<<"\t\t\t\t\t| Address: "<<address<<"		|"<<endl
			<<"\t\t\t\t\t| Status: "<<status<<"			|"<<endl
			<<"\t\t\t\t\t|					|"<<endl
			<<"\t\t\t\t\t-----------------------------------------"<<endl;
			
		cout<<"\n\n\t\t\t\t\tPress any key to go to Welcome Menu";

		if(getch()) {
			system("CLS");
			welcomeMenu();
		}
		
	}
	else {
		cout<<"\n\n\t\t\t\t\t-----------------------------------------"<<endl
			<<"\t\t\t\t\t|	     No Result Found		|"<<endl
			<<"\t\t\t\t\t-----------------------------------------"<<endl;
			
		cout<<"\n\n\t\t\t\t\tPress any key to go to Welcome Menu";
		if(getch()) {
			system("CLS");
			welcomeMenu();
		}
			
	}
	
}

/*--- Creating class for Admin's login credentials ---*/
class AdminAuthentication {
	private:
		string adminUsername, adminPassword;
	public:
		AdminAuthentication(); //Initializing Data Members
		friend void adminLoginInterface(); //Creating a friend function

};
AdminAuthentication::AdminAuthentication() {
	adminUsername= "admin321";
	adminPassword= "OOP123";
}

/*--- Creating abstract class for Admin Panel's Functionalities ---*/
class AdminPanelOptions {
	protected:
		int byApplicantID, listChoiceNum;
		bool choiceNumError;
		bool applicantFound;
		int changeChoice;
		bool changeChoiceError;
	public:
		virtual void applicantsList()= 0; //Creating Pure Virtual Function
		virtual void applicantIdInput()=0; //Creating Pure Virtual Function
		virtual void selectApplicant(int)= 0; //Creating Pure Virtual Function
		virtual void approveApplicaton(int)= 0; //Creating Pure Virtual Function
		virtual void rejectApplication(int)= 0; //Creating Pure Virtual Function
		AdminPanelOptions(); //Creating Constructor to initialize data members
};
AdminPanelOptions::AdminPanelOptions() {
	applicantFound= true;
	changeChoice=0;
	changeChoiceError= false;
}

/*--- Creating class for pending applicants functionalities ---*/
class PendingApplicants: public AdminPanelOptions, protected NewApplicant {
	public:
		virtual void applicantsList();
		virtual void applicantIdInput();
		virtual void selectApplicant(int);
		virtual void approveApplicaton(int);
		virtual void rejectApplication(int);
};
void PendingApplicants::applicantsList() {

	choiceNumError= false;
	
	while(true) {

		system("CLS");

		fstream approvedApplicantsList("pendingFile.txt", ios::in);

		cout<<"\n\n\n\t\t\t\t\t-----------------------------------------"<<endl
				<<"\t\t\t\t\t|	Passport Management System	|"<<endl
				<<"\t\t\t\t\t-----------------------------------------"<<endl
				<<"\t\t\t\t\t|	    Pending Applicants		|"<<endl
				<<"\t\t\t\t\t-----------------------------------------"<<endl;
		cout<<"\t-------------------------------------------------------------------------------------------------------"<<endl
			<<"\t|Applicant ID		Name		Father Name		Gender		CNIC		Status|"<<endl
			<<"\t-------------------------------------------------------------------------------------------------------"<<endl;

		while (approvedApplicantsList>>applicationID>>name>>fatherName>>dateOfBirth>>gender>>nationality>>placeOfBirth>>cnic>>address>>age>>status) {
			if(status=="Pending") {

				name= staracToSpace(name);
				fatherName= staracToSpace(fatherName);
				placeOfBirth= staracToSpace(placeOfBirth);
				address= staracToSpace(address);

				cout<<"\t|  "<<applicationID<<"		  "<<name<<"		"<<fatherName<<"		"<<gender<<"	     "<<cnic<<"	      "<<status<<"|"<<endl;
			}
		}
		cout<<"\t-------------------------------------------------------------------------------------------------------"<<endl<<endl;

		approvedApplicantsList.close();

		if(choiceNumError== true) {
			cout<<"\t\t\t\t\t*Error: Invalid Choice Number!"<<endl<<endl;
		}
		

		cout<<"\t\t\t\t\tPress '1' to select Applicant by ID"<<endl
			<<"\t\t\t\t\tPress '2' to go Back"<<endl<<endl;
		
		cout<<"\t\t\t\t\tEnter your choice: ";
		cin>>listChoiceNum;

		if(listChoiceNum==1) {
			applicantIdInput();
			break;
		}
		else if(listChoiceNum==2) {
			adminPanelInterface();
			break;
		}
		else  {
			choiceNumError= true;
			continue;
		}
	}
	
}
void PendingApplicants::applicantIdInput() {
	
	bool applicantIdInput= false, loopBreak= false;

	while(true) {

		if(loopBreak== true) {
			cout<<"\n\t\t\t\t\t*Error: Applicant Not Found";
		}

		cout<<"\n\n\t\t\t\t\tEnter Applicant ID to select: ";
		cin>>byApplicantID;

		fstream approvedSelect("pendingFile.txt", ios::in);

		while (approvedSelect>>applicationID>>name>>fatherName>>dateOfBirth>>gender>>nationality>>placeOfBirth>>cnic>>address>>age>>status) {
				
			if((applicationID == byApplicantID) && (status == "Pending")) {
				applicantIdInput= true;
			}
		}
		approvedSelect.close();

		if(applicantIdInput== true) {
			selectApplicant(byApplicantID);
			break;
		}
		else {
			loopBreak= true;
			continue;
		}
	}
}
void PendingApplicants::selectApplicant(int byApplicantID) {

	
	while(true) {

		fstream approvedSelect("pendingFile.txt", ios::in);

		while (approvedSelect>>applicationID>>name>>fatherName>>dateOfBirth>>gender>>nationality>>placeOfBirth>>cnic>>address>>age>>status) {
			
			if((applicationID == byApplicantID)) {

				system("CLS");

				name= staracToSpace(name);
				fatherName= staracToSpace(fatherName);
				placeOfBirth= staracToSpace(placeOfBirth);
				address= staracToSpace(address);

				cout<<"\n\n\n\t\t\t\t\t-----------------------------------------"<<endl
					<<"\t\t\t\t\t|	Passport Management System	|"<<endl
					<<"\t\t\t\t\t-----------------------------------------"<<endl
					<<"\t\t\t\t\t|	     Applicant Found		|"<<endl
					<<"\t\t\t\t\t|					|"<<endl;
					
				cout<<"\t\t\t\t\t| Applicant ID: "<<applicationID<<"			|"<<endl
					<<"\t\t\t\t\t| Name: "<<name<<"			|"<<endl
					<<"\t\t\t\t\t| Father's Name: "<<fatherName<<"		|"<<endl
					<<"\t\t\t\t\t| Date of Birth (DD-MM-YY): "<<dateOfBirth<<"	|"<<endl
					<<"\t\t\t\t\t| Age: "<<age<<"				|"<<endl
					<<"\t\t\t\t\t| Gender: "<<gender<<"				|"<<endl
					<<"\t\t\t\t\t| Birth Place: "<<placeOfBirth<<"	|"<<endl
					<<"\t\t\t\t\t| Nationality: "<<nationality<<"		|"<<endl
					<<"\t\t\t\t\t| CNIC: "<<cnic<<"			|"<<endl
					<<"\t\t\t\t\t| Address: "<<address<<"		|"<<endl
					<<"\t\t\t\t\t| Status: "<<status<<"			|"<<endl
					<<"\t\t\t\t\t|					|"<<endl
					<<"\t\t\t\t\t-----------------------------------------"<<endl;

				applicantFound= true;

				approvedSelect.close();

				cout<<"\n\t\t\t\t\tPress '1' to Approve Applicant"<<endl
					<<"\t\t\t\t\tPress '2' to Reject Applicant"<<endl
					<<"\t\t\t\t\tPress '3' to go Back"<<endl;

				if(changeChoiceError==true) {
					cout<<"\n\t\t\t\t\t*Error: Invalid Choice Input!"<<endl;
				}

				cout<<"\n\t\t\t\t\tEnter your Choice: ";
				cin>>changeChoice;

				if(changeChoice==1) {
					approveApplicaton(byApplicantID);
					break;
				}
				else if(changeChoice==2) {
					rejectApplication(byApplicantID);
					break;
				}
				else if(changeChoice==3) {
					applicantsList();
				}
			}
		}
		if(applicantFound==false) {
			cout<<"\n\n\t\t\t\t\t*Error: Applicant Not Found!"<<endl<<endl;
		}
	if(changeChoice!=1 && changeChoice!=2 && changeChoice!=3) {
		changeChoiceError= true;
		continue;
		}
	}
}
void PendingApplicants::approveApplicaton(int byApplicantID) {

	fstream oldFile("pendingFile.txt", ios::in);
	fstream newFile("temp.txt", ios::out);

	while(oldFile>>applicationID>>name>>fatherName>>dateOfBirth>>gender>>nationality>>placeOfBirth>>cnic>>address>>age>>status) {
		if(byApplicantID==applicationID) {
			status= "Approved";
			newFile<<applicationID<<" "<<name<<" "<<fatherName<<" "<<dateOfBirth<<" "<<gender<<" "<<nationality<<" "<<placeOfBirth<<" "<<cnic<<" "<<address<<" "<<age<<" "<<status<<endl;
		}
		else if(byApplicantID!=applicationID) {
			newFile<<applicationID<<" "<<name<<" "<<fatherName<<" "<<dateOfBirth<<" "<<gender<<" "<<nationality<<" "<<placeOfBirth<<" "<<cnic<<" "<<address<<" "<<age<<" "<<status<<endl;
		}
	}

	oldFile.close();
	newFile.close();

	remove("pendingFile.txt");
	rename("temp.txt", "pendingFile.txt");

	selectApplicant(byApplicantID);

}
void PendingApplicants::rejectApplication(int byApplicantID) {

	fstream oldFile("pendingFile.txt", ios::in);
	fstream newFile("temp.txt", ios::out);

	while(oldFile>>applicationID>>name>>fatherName>>dateOfBirth>>gender>>nationality>>placeOfBirth>>cnic>>address>>age>>status) {
		if(byApplicantID==applicationID) {
			status= "Rejected";
			newFile<<applicationID<<" "<<name<<" "<<fatherName<<" "<<dateOfBirth<<" "<<gender<<" "<<nationality<<" "<<placeOfBirth<<" "<<cnic<<" "<<address<<" "<<age<<" "<<status<<endl;
		}
		else if(byApplicantID!=applicationID) {
			newFile<<applicationID<<" "<<name<<" "<<fatherName<<" "<<dateOfBirth<<" "<<gender<<" "<<nationality<<" "<<placeOfBirth<<" "<<cnic<<" "<<address<<" "<<age<<" "<<status<<endl;
		}
	}

	oldFile.close();
	newFile.close();

	remove("pendingFile.txt");
	rename("temp.txt", "pendingFile.txt");

	selectApplicant(byApplicantID);

}

/*--- Creating class for approved applicants functionalities ---*/
class ApprovedApplicants: public AdminPanelOptions, protected NewApplicant {
	public:
		virtual void applicantsList();
		virtual void applicantIdInput();
		virtual void selectApplicant(int);
		virtual void approveApplicaton(int);
		virtual void rejectApplication(int);
};
void ApprovedApplicants::applicantsList() {

	choiceNumError= false;
	
	while(true) {

		system("CLS");

		fstream approvedApplicantsList("pendingFile.txt", ios::in);

		cout<<"\n\n\n\t\t\t\t\t-----------------------------------------"<<endl
				<<"\t\t\t\t\t|	Passport Management System	|"<<endl
				<<"\t\t\t\t\t-----------------------------------------"<<endl
				<<"\t\t\t\t\t|	    Approved Applicants		|"<<endl
				<<"\t\t\t\t\t-----------------------------------------"<<endl;
		cout<<"\t-------------------------------------------------------------------------------------------------------"<<endl
			<<"\t|Applicant ID		Name		Father Name		Gender		CNIC		Status|"<<endl
			<<"\t-------------------------------------------------------------------------------------------------------"<<endl;

		while (approvedApplicantsList>>applicationID>>name>>fatherName>>dateOfBirth>>gender>>nationality>>placeOfBirth>>cnic>>address>>age>>status) {
			if(status=="Approved") {

				name= staracToSpace(name);
				fatherName= staracToSpace(fatherName);
				placeOfBirth= staracToSpace(placeOfBirth);
				address= staracToSpace(address);

				cout<<"\t|  "<<applicationID<<"		  "<<name<<"		"<<fatherName<<"		"<<gender<<"	     "<<cnic<<"	      "<<status<<"|"<<endl;
			}
		}
		cout<<"\t-------------------------------------------------------------------------------------------------------"<<endl<<endl;

		approvedApplicantsList.close();

		if(choiceNumError== true) {
			cout<<"\t\t\t\t\t*Error: Invalid Choice Number!"<<endl<<endl;
		}
		

		cout<<"\t\t\t\t\tPress '1' to select Applicant by ID"<<endl
			<<"\t\t\t\t\tPress '2' to go Back"<<endl<<endl;
		
		cout<<"\t\t\t\t\tEnter your choice: ";
		cin>>listChoiceNum;

		if(listChoiceNum==1) {
			applicantIdInput();
			break;
		}
		else if(listChoiceNum==2) {
			adminPanelInterface();
			break;
		}
		else  {
			choiceNumError= true;
			continue;
		}
	}
	
}
void ApprovedApplicants::applicantIdInput() {
	
	bool applicantIdInput= false, loopBreak= false;

	while(true) {

		if(loopBreak== true) {
			cout<<"\n\t\t\t\t\t*Error: Applicant Not Found";
		}

		cout<<"\n\n\t\t\t\t\tEnter Applicant ID to select: ";
		cin>>byApplicantID;

		fstream approvedSelect("pendingFile.txt", ios::in);

		while (approvedSelect>>applicationID>>name>>fatherName>>dateOfBirth>>gender>>nationality>>placeOfBirth>>cnic>>address>>age>>status) {
				
			if((applicationID == byApplicantID) && (status == "Approved")) {
				applicantIdInput= true;
			}
		}
		approvedSelect.close();

		if(applicantIdInput== true) {
			selectApplicant(byApplicantID);
			break;
		}
		else {
			loopBreak= true;
			continue;
		}
	}
}
void ApprovedApplicants::selectApplicant(int byApplicantID) {

	
	while(true) {

		fstream approvedSelect("pendingFile.txt", ios::in);

		while (approvedSelect>>applicationID>>name>>fatherName>>dateOfBirth>>gender>>nationality>>placeOfBirth>>cnic>>address>>age>>status) {
			
			if((applicationID == byApplicantID)) {

				system("CLS");

				name= staracToSpace(name);
				fatherName= staracToSpace(fatherName);
				placeOfBirth= staracToSpace(placeOfBirth);
				address= staracToSpace(address);

				cout<<"\n\n\n\t\t\t\t\t-----------------------------------------"<<endl
					<<"\t\t\t\t\t|	Passport Management System	|"<<endl
					<<"\t\t\t\t\t-----------------------------------------"<<endl
					<<"\t\t\t\t\t|	     Applicant Found		|"<<endl
					<<"\t\t\t\t\t|					|"<<endl;
					
				cout<<"\t\t\t\t\t| Applicant ID: "<<applicationID<<"			|"<<endl
					<<"\t\t\t\t\t| Name: "<<name<<"			|"<<endl
					<<"\t\t\t\t\t| Father's Name: "<<fatherName<<"		|"<<endl
					<<"\t\t\t\t\t| Date of Birth (DD-MM-YY): "<<dateOfBirth<<"	|"<<endl
					<<"\t\t\t\t\t| Age: "<<age<<"				|"<<endl
					<<"\t\t\t\t\t| Gender: "<<gender<<"				|"<<endl
					<<"\t\t\t\t\t| Birth Place: "<<placeOfBirth<<"	|"<<endl
					<<"\t\t\t\t\t| Nationality: "<<nationality<<"		|"<<endl
					<<"\t\t\t\t\t| CNIC: "<<cnic<<"			|"<<endl
					<<"\t\t\t\t\t| Address: "<<address<<"		|"<<endl
					<<"\t\t\t\t\t| Status: "<<status<<"			|"<<endl
					<<"\t\t\t\t\t|					|"<<endl
					<<"\t\t\t\t\t-----------------------------------------"<<endl;

				applicantFound= true;

				approvedSelect.close();

				cout<<"\n\t\t\t\t\tPress '1' to Approve Applicant"<<endl
					<<"\t\t\t\t\tPress '2' to Reject Applicant"<<endl
					<<"\t\t\t\t\tPress '3' to go Back"<<endl;

				if(changeChoiceError==true) {
					cout<<"\n\t\t\t\t\t*Error: Invalid Choice Input!"<<endl;
				}

				cout<<"\n\t\t\t\t\tEnter your Choice: ";
				cin>>changeChoice;

				if(changeChoice==1) {
					approveApplicaton(byApplicantID);
					break;
				}
				else if(changeChoice==2) {
					rejectApplication(byApplicantID);
					break;
				}
				else if(changeChoice==3) {
					applicantsList();
				}
			}
		}
		if(applicantFound==false) {
			cout<<"\n\n\t\t\t\t\t*Error: Applicant Not Found!"<<endl<<endl;
		}
	if(changeChoice!=1 && changeChoice!=2 && changeChoice!=3) {
		changeChoiceError= true;
		continue;
		}
	}
}
void ApprovedApplicants::approveApplicaton(int byApplicantID) {

	fstream oldFile("pendingFile.txt", ios::in);
	fstream newFile("temp.txt", ios::out);

	while(oldFile>>applicationID>>name>>fatherName>>dateOfBirth>>gender>>nationality>>placeOfBirth>>cnic>>address>>age>>status) {
		if(byApplicantID==applicationID) {
			status= "Approved";
			newFile<<applicationID<<" "<<name<<" "<<fatherName<<" "<<dateOfBirth<<" "<<gender<<" "<<nationality<<" "<<placeOfBirth<<" "<<cnic<<" "<<address<<" "<<age<<" "<<status<<endl;
		}
		else if(byApplicantID!=applicationID) {
			newFile<<applicationID<<" "<<name<<" "<<fatherName<<" "<<dateOfBirth<<" "<<gender<<" "<<nationality<<" "<<placeOfBirth<<" "<<cnic<<" "<<address<<" "<<age<<" "<<status<<endl;
		}
	}

	oldFile.close();
	newFile.close();

	remove("pendingFile.txt");
	rename("temp.txt", "pendingFile.txt");

	selectApplicant(byApplicantID);

}
void ApprovedApplicants::rejectApplication(int byApplicantID) {

	fstream oldFile("pendingFile.txt", ios::in);
	fstream newFile("temp.txt", ios::out);

	while(oldFile>>applicationID>>name>>fatherName>>dateOfBirth>>gender>>nationality>>placeOfBirth>>cnic>>address>>age>>status) {
		if(byApplicantID==applicationID) {
			status= "Rejected";
			newFile<<applicationID<<" "<<name<<" "<<fatherName<<" "<<dateOfBirth<<" "<<gender<<" "<<nationality<<" "<<placeOfBirth<<" "<<cnic<<" "<<address<<" "<<age<<" "<<status<<endl;
		}
		else if(byApplicantID!=applicationID) {
			newFile<<applicationID<<" "<<name<<" "<<fatherName<<" "<<dateOfBirth<<" "<<gender<<" "<<nationality<<" "<<placeOfBirth<<" "<<cnic<<" "<<address<<" "<<age<<" "<<status<<endl;
		}
	}

	oldFile.close();
	newFile.close();

	remove("pendingFile.txt");
	rename("temp.txt", "pendingFile.txt");

	selectApplicant(byApplicantID);

}

/*--- Creating class for rejected applicants functionalities ---*/
class RejectedApplicants: public AdminPanelOptions, protected NewApplicant {
	public:
		virtual void applicantsList();
		virtual void applicantIdInput();
		virtual void selectApplicant(int);
		virtual void approveApplicaton(int);
		virtual void rejectApplication(int);
};
void RejectedApplicants::applicantsList() {

	choiceNumError= false;
	
	while(true) {

		system("CLS");

		fstream approvedApplicantsList("pendingFile.txt", ios::in);

		cout<<"\n\n\n\t\t\t\t\t-----------------------------------------"<<endl
				<<"\t\t\t\t\t|	Passport Management System	|"<<endl
				<<"\t\t\t\t\t-----------------------------------------"<<endl
				<<"\t\t\t\t\t|	    Rejected Applicants		|"<<endl
				<<"\t\t\t\t\t-----------------------------------------"<<endl;
		cout<<"\t-------------------------------------------------------------------------------------------------------"<<endl
			<<"\t|Applicant ID		Name		Father Name		Gender		CNIC		Status|"<<endl
			<<"\t-------------------------------------------------------------------------------------------------------"<<endl;

		while (approvedApplicantsList>>applicationID>>name>>fatherName>>dateOfBirth>>gender>>nationality>>placeOfBirth>>cnic>>address>>age>>status) {
			if(status=="Rejected") {

				name= staracToSpace(name);
				fatherName= staracToSpace(fatherName);
				placeOfBirth= staracToSpace(placeOfBirth);
				address= staracToSpace(address);

				cout<<"\t|  "<<applicationID<<"		  "<<name<<"		"<<fatherName<<"		"<<gender<<"	     "<<cnic<<"	      "<<status<<"|"<<endl;
			}
		}
		cout<<"\t-------------------------------------------------------------------------------------------------------"<<endl<<endl;

		approvedApplicantsList.close();

		if(choiceNumError== true) {
			cout<<"\t\t\t\t\t*Error: Invalid Choice Number!"<<endl<<endl;
		}
		

		cout<<"\t\t\t\t\tPress '1' to select Applicant by ID"<<endl
			<<"\t\t\t\t\tPress '2' to go Back"<<endl<<endl;
		
		cout<<"\t\t\t\t\tEnter your choice: ";
		cin>>listChoiceNum;

		if(listChoiceNum==1) {
			applicantIdInput();
			break;
		}
		else if(listChoiceNum==2) {
			adminPanelInterface();
			break;
		}
		else  {
			choiceNumError= true;
			continue;
		}
	}
	
}
void RejectedApplicants::applicantIdInput() {
	
	bool applicantIdInput= false, loopBreak= false;

	while(true) {

		if(loopBreak== true) {
			cout<<"\n\t\t\t\t\t*Error: Applicant Not Found";
		}

		cout<<"\n\n\t\t\t\t\tEnter Applicant ID to select: ";
		cin>>byApplicantID;

		fstream approvedSelect("pendingFile.txt", ios::in);

		while (approvedSelect>>applicationID>>name>>fatherName>>dateOfBirth>>gender>>nationality>>placeOfBirth>>cnic>>address>>age>>status) {
				
			if((applicationID == byApplicantID) && (status == "Rejected")) {
				applicantIdInput= true;
			}
		}
		approvedSelect.close();

		if(applicantIdInput== true) {
			selectApplicant(byApplicantID);
			break;
		}
		else {
			loopBreak= true;
			continue;
		}
	}
}
void RejectedApplicants::selectApplicant(int byApplicantID) {

	
	while(true) {

		fstream approvedSelect("pendingFile.txt", ios::in);

		while (approvedSelect>>applicationID>>name>>fatherName>>dateOfBirth>>gender>>nationality>>placeOfBirth>>cnic>>address>>age>>status) {
			
			if((applicationID == byApplicantID)) {

				system("CLS");

				name= staracToSpace(name);
				fatherName= staracToSpace(fatherName);
				placeOfBirth= staracToSpace(placeOfBirth);
				address= staracToSpace(address);

				cout<<"\n\n\n\t\t\t\t\t-----------------------------------------"<<endl
					<<"\t\t\t\t\t|	Passport Management System	|"<<endl
					<<"\t\t\t\t\t-----------------------------------------"<<endl
					<<"\t\t\t\t\t|	     Applicant Found		|"<<endl
					<<"\t\t\t\t\t|					|"<<endl;
					
				cout<<"\t\t\t\t\t| Applicant ID: "<<applicationID<<"			|"<<endl
					<<"\t\t\t\t\t| Name: "<<name<<"			|"<<endl
					<<"\t\t\t\t\t| Father's Name: "<<fatherName<<"		|"<<endl
					<<"\t\t\t\t\t| Date of Birth (DD-MM-YY): "<<dateOfBirth<<"	|"<<endl
					<<"\t\t\t\t\t| Age: "<<age<<"				|"<<endl
					<<"\t\t\t\t\t| Gender: "<<gender<<"				|"<<endl
					<<"\t\t\t\t\t| Birth Place: "<<placeOfBirth<<"	|"<<endl
					<<"\t\t\t\t\t| Nationality: "<<nationality<<"		|"<<endl
					<<"\t\t\t\t\t| CNIC: "<<cnic<<"			|"<<endl
					<<"\t\t\t\t\t| Address: "<<address<<"		|"<<endl
					<<"\t\t\t\t\t| Status: "<<status<<"			|"<<endl
					<<"\t\t\t\t\t|					|"<<endl
					<<"\t\t\t\t\t-----------------------------------------"<<endl;

				applicantFound= true;

				approvedSelect.close();

				cout<<"\n\t\t\t\t\tPress '1' to Approve Applicant"<<endl
					<<"\t\t\t\t\tPress '2' to Reject Applicant"<<endl
					<<"\t\t\t\t\tPress '3' to go Back"<<endl;

				if(changeChoiceError==true) {
					cout<<"\n\t\t\t\t\t*Error: Invalid Choice Input!"<<endl;
				}

				cout<<"\n\t\t\t\t\tEnter your Choice: ";
				cin>>changeChoice;

				if(changeChoice==1) {
					approveApplicaton(byApplicantID);
					break;
				}
				else if(changeChoice==2) {
					rejectApplication(byApplicantID);
					break;
				}
				else if(changeChoice==3) {
					applicantsList();
				}
			}
		}
		if(applicantFound==false) {
			cout<<"\n\n\t\t\t\t\t*Error: Applicant Not Found!"<<endl<<endl;
		}
	if(changeChoice!=1 && changeChoice!=2 && changeChoice!=3) {
		changeChoiceError= true;
		continue;
		}
	}
}
void RejectedApplicants::approveApplicaton(int byApplicantID) {

	fstream oldFile("pendingFile.txt", ios::in);
	fstream newFile("temp.txt", ios::out);

	while(oldFile>>applicationID>>name>>fatherName>>dateOfBirth>>gender>>nationality>>placeOfBirth>>cnic>>address>>age>>status) {
		if(byApplicantID==applicationID) {
			status= "Approved";
			newFile<<applicationID<<" "<<name<<" "<<fatherName<<" "<<dateOfBirth<<" "<<gender<<" "<<nationality<<" "<<placeOfBirth<<" "<<cnic<<" "<<address<<" "<<age<<" "<<status<<endl;
		}
		else if(byApplicantID!=applicationID) {
			newFile<<applicationID<<" "<<name<<" "<<fatherName<<" "<<dateOfBirth<<" "<<gender<<" "<<nationality<<" "<<placeOfBirth<<" "<<cnic<<" "<<address<<" "<<age<<" "<<status<<endl;
		}
	}

	oldFile.close();
	newFile.close();

	remove("pendingFile.txt");
	rename("temp.txt", "pendingFile.txt");

	selectApplicant(byApplicantID);

}
void RejectedApplicants::rejectApplication(int byApplicantID) {

	fstream oldFile("pendingFile.txt", ios::in);
	fstream newFile("temp.txt", ios::out);

	while(oldFile>>applicationID>>name>>fatherName>>dateOfBirth>>gender>>nationality>>placeOfBirth>>cnic>>address>>age>>status) {
		if(byApplicantID==applicationID) {
			status= "Rejected";
			newFile<<applicationID<<" "<<name<<" "<<fatherName<<" "<<dateOfBirth<<" "<<gender<<" "<<nationality<<" "<<placeOfBirth<<" "<<cnic<<" "<<address<<" "<<age<<" "<<status<<endl;
		}
		else if(byApplicantID!=applicationID) {
			newFile<<applicationID<<" "<<name<<" "<<fatherName<<" "<<dateOfBirth<<" "<<gender<<" "<<nationality<<" "<<" "<<placeOfBirth<<" "<<cnic<<" "<<address<<" "<<age<<" "<<status<<endl;
		}
	}

	oldFile.close();
	newFile.close();

	remove("pendingFile.txt");
	rename("temp.txt", "pendingFile.txt");

	selectApplicant(byApplicantID);

}

/*--- Creating class search applicant using containership ---*/
class AdminSearch: public AdminPanelOptions {

	NewApplicant applicant; //Containership (has-a relationship)

	public:
		virtual void applicantsList();
		virtual void applicantIdInput();
		virtual void selectApplicant(int);
		virtual void approveApplicaton(int);
		virtual void rejectApplication(int);
};
void AdminSearch::applicantsList() {}
void AdminSearch::applicantIdInput() {
	
	bool applicantIdInput= false, loopBreak= false;

	while(true) {

		if(loopBreak== true) {
			cout<<"\n\t\t\t\t\t*Error: Applicant Not Found";
		}

		cout<<"\n\n\t\t\t\t\tEnter Applicant ID to select: ";
		cin>>byApplicantID;

		fstream approvedSelect("pendingFile.txt", ios::in);

		while (approvedSelect>>applicant.applicationID>>applicant.name>>applicant.fatherName>>applicant.dateOfBirth>>applicant.gender>>applicant.nationality>>applicant.placeOfBirth>>applicant.cnic>>applicant.address>>applicant.age>>applicant.status) {
				
			if((applicant.applicationID == byApplicantID)) {
				applicantIdInput= true;
			}
		}
		approvedSelect.close();

		if(applicantIdInput== true) {
			selectApplicant(byApplicantID);
			break;
		}
		else {
			loopBreak= true;
			continue;
		}
	}
}
void AdminSearch::selectApplicant(int byApplicantID) {

	
	while(true) {

		fstream approvedSelect("pendingFile.txt", ios::in);

		while (approvedSelect>>applicant.applicationID>>applicant.name>>applicant.fatherName>>applicant.dateOfBirth>>applicant.gender>>applicant.nationality>>applicant.placeOfBirth>>applicant.cnic>>applicant.address>>applicant.age>>applicant.status) {
			
			if((applicant.applicationID == byApplicantID)) {

				system("CLS");

				applicant.name= staracToSpace(applicant.name);
				applicant.fatherName= staracToSpace(applicant.fatherName);
				applicant.placeOfBirth= staracToSpace(applicant.placeOfBirth);
				applicant.address= staracToSpace(applicant.address);

				cout<<applicant; //Overloaded Operator Call

				applicantFound= true;

				approvedSelect.close();

				cout<<"\n\t\t\t\t\tPress '1' to Approve Applicant"<<endl
					<<"\t\t\t\t\tPress '2' to Reject Applicant"<<endl
					<<"\t\t\t\t\tPress '3' to go Back"<<endl;

				if(changeChoiceError==true) {
					cout<<"\n\t\t\t\t\t*Error: Invalid Choice Input!"<<endl;
				}

				cout<<"\n\t\t\t\t\tEnter your Choice: ";
				cin>>changeChoice;

				if(changeChoice==1) {
					approveApplicaton(byApplicantID);
					break;
				}
				else if(changeChoice==2) {
					rejectApplication(byApplicantID);
					break;
				}
				else if(changeChoice==3) {
					adminPanelInterface();
				}
			}
		}
		if(applicantFound==false) {
			cout<<"\n\n\t\t\t\t\t*Error: Applicant Not Found!"<<endl<<endl;
		}
	if(changeChoice!=1 && changeChoice!=2 && changeChoice!=3) {
		changeChoiceError= true;
		continue;
		}
	}
}
void AdminSearch::approveApplicaton(int byApplicantID) {

	fstream oldFile("pendingFile.txt", ios::in);
	fstream newFile("temp.txt", ios::out);

	while(oldFile>>applicant.applicationID>>applicant.name>>applicant.fatherName>>applicant.dateOfBirth>>applicant.gender>>applicant.nationality>>applicant.placeOfBirth>>applicant.cnic>>applicant.address>>applicant.age>>applicant.status) {
		if(byApplicantID==applicant.applicationID) {
			applicant.status= "Approved";
			newFile<<applicant.applicationID<<" "<<applicant.name<<" "<<applicant.fatherName<<" "<<applicant.dateOfBirth<<" "<<applicant.gender<<" "<<applicant.nationality<<" "<<applicant.placeOfBirth<<" "<<applicant.cnic<<" "<<applicant.address<<" "<<applicant.age<<" "<<applicant.status<<endl;
		}
		else if(byApplicantID!=applicant.applicationID) {
			newFile<<applicant.applicationID<<" "<<applicant.name<<" "<<applicant.fatherName<<" "<<applicant.dateOfBirth<<" "<<applicant.gender<<" "<<applicant.nationality<<" "<<applicant.placeOfBirth<<" "<<applicant.cnic<<" "<<applicant.address<<" "<<applicant.age<<" "<<applicant.status<<endl;
		}
	}

	oldFile.close();
	newFile.close();

	remove("pendingFile.txt");
	rename("temp.txt", "pendingFile.txt");

	selectApplicant(byApplicantID);

}
void AdminSearch::rejectApplication(int byApplicantID) {

	fstream oldFile("pendingFile.txt", ios::in);
	fstream newFile("temp.txt", ios::out);

	while(oldFile>>applicant.applicationID>>applicant.name>>applicant.fatherName>>applicant.dateOfBirth>>applicant.gender>>applicant.nationality>>applicant.placeOfBirth>>applicant.cnic>>applicant.address>>applicant.age>>applicant.status) {
		if(byApplicantID==applicant.applicationID) {
			applicant.status= "Rejected";
			newFile<<applicant.applicationID<<" "<<applicant.name<<" "<<applicant.fatherName<<" "<<applicant.dateOfBirth<<" "<<applicant.gender<<" "<<applicant.nationality<<" "<<applicant.placeOfBirth<<" "<<applicant.cnic<<" "<<applicant.address<<" "<<applicant.age<<" "<<applicant.status<<endl;
		}
		else if(byApplicantID!=applicant.applicationID) {
			newFile<<applicant.applicationID<<" "<<applicant.name<<" "<<applicant.fatherName<<" "<<applicant.dateOfBirth<<" "<<applicant.gender<<" "<<applicant.nationality<<" "<<applicant.placeOfBirth<<" "<<applicant.cnic<<" "<<applicant.address<<" "<<applicant.age<<" "<<applicant.status<<endl;
		}
	}

	oldFile.close();
	newFile.close();

	remove("pendingFile.txt");
	rename("temp.txt", "pendingFile.txt");

	selectApplicant(byApplicantID);

}

/*--- Creating Global Operator Overloading Function ---*/
ostream& operator << (ostream& print, NewApplicant& applicant) {

	cout<<"\n\n\n\t\t\t\t\t-----------------------------------------"<<endl
		<<"\t\t\t\t\t|	Passport Management System	|"<<endl
		<<"\t\t\t\t\t-----------------------------------------"<<endl
		<<"\t\t\t\t\t|	     Applicant Found		|"<<endl
		<<"\t\t\t\t\t|					|"<<endl;
					
	cout<<"\t\t\t\t\t| Applicant ID: "<<applicant.applicationID<<"			|"<<endl
		<<"\t\t\t\t\t| Name: "<<applicant.name<<"			|"<<endl
		<<"\t\t\t\t\t| Father's Name: "<<applicant.fatherName<<"		|"<<endl
		<<"\t\t\t\t\t| Date of Birth (DD-MM-YY): "<<applicant.dateOfBirth<<"	|"<<endl
		<<"\t\t\t\t\t| Age: "<<applicant.age<<"				|"<<endl
		<<"\t\t\t\t\t| Gender: "<<applicant.gender<<"				|"<<endl
		<<"\t\t\t\t\t| Birth Place: "<<applicant.placeOfBirth<<"	|"<<endl
		<<"\t\t\t\t\t| Nationality: "<<applicant.nationality<<"		|"<<endl
		<<"\t\t\t\t\t| CNIC: "<<applicant.cnic<<"			|"<<endl
		<<"\t\t\t\t\t| Address: "<<applicant.address<<"		|"<<endl
		<<"\t\t\t\t\t| Status: "<<applicant.status<<"			|"<<endl
		<<"\t\t\t\t\t|					|"<<endl
		<<"\t\t\t\t\t-----------------------------------------"<<endl;

	return print;
}

int main() {
		
	welcomeMenu();

}

void welcomeMenu() {
	
	int welcomeChoice=0;
	bool welcomeError= false;
	
	while(true) {		
		cout<<"\n\n\n\t\t\t\t\t-----------------------------------------"<<endl
			<<"\t\t\t\t\t|	Passport Management System	|"<<endl
			<<"\t\t\t\t\t-----------------------------------------"<<endl
			<<"\t\t\t\t\t|		Welcome Menu		|"<<endl
			<<"\t\t\t\t\t|					|"<<endl;
		
		cout<<"\t\t\t\t\t| Press '1' to login as admin		|"<<endl
			<<"\t\t\t\t\t| Press '2' to apply for passport	|"<<endl
			<<"\t\t\t\t\t| Press '3' to check passport approval	|"<<endl
			<<"\t\t\t\t\t|					|"<<endl
			<<"\t\t\t\t\t-----------------------------------------"<<endl;
				
		if(welcomeError==true) {
			cout<<"\n\t\t\t\t\t*Error: Invalid Choice Number!"<<endl;
		}
				
		cout<<"\n\t\t\t\t\tEnter your Choice: ";
		cin>>welcomeChoice;
			
		if(welcomeChoice==1) {
			adminLoginInterface();
			break;
		}
		else if(welcomeChoice==2) {
			applyForPassport();
			break;
		}
		else if(welcomeChoice==3) {
			ApplicantSearch search;
			break;
		}
		else {
			welcomeError= true;
			system("CLS");
			continue;
		}
	}
	
}

void applyForPassport() {
	
	system("CLS");
	cout<<"\n\n\n\t\t\t\t\t-----------------------------------------"<<endl
		<<"\t\t\t\t\t|	Passport Management System	|"<<endl
		<<"\t\t\t\t\t-----------------------------------------"<<endl
		<<"\t\t\t\t\t|	    Registartion Form		|"<<endl
		<<"\t\t\t\t\t-----------------------------------------"<<endl;
	
	NewApplicant application;
	application.application();
	
}

void adminLoginInterface() {
	string userNameInput, passwordInput;
	bool adminLoginError= false;
	
	while(true) {
		system("CLS");
		cout<<"\n\n\n\t\t\t\t\t-----------------------------------------"<<endl
			<<"\t\t\t\t\t|	Passport Management System	|"<<endl
			<<"\t\t\t\t\t-----------------------------------------"<<endl
			<<"\t\t\t\t\t|	   	Admin Login		|"<<endl
			<<"\t\t\t\t\t-----------------------------------------"<<endl;
		
		if(adminLoginError== true) {
			cout<<"\n\t\t\t\t\t*Error: Invalid Username or Password"<<endl;
		}

		cout<<"\n\t\t\t\t\tEnter Username: ";
		cin>>userNameInput;
		cout<<"\n\t\t\t\t\tEnter Password: ";
		cin.ignore();
		getline(cin,passwordInput);

		AdminAuthentication loginCredentials;
		if(userNameInput == loginCredentials.adminUsername && passwordInput == loginCredentials.adminPassword) {
			adminPanelInterface();
			break;
		}
		else {
			adminLoginError= true;
			continue;
		}
		
	}
}

void adminPanelInterface() {

	int adminPanelChoice;
	bool adminOptionError= false;

	while(true) {
		system("CLS");

		cout<<"\n\n\n\t\t\t\t\t-----------------------------------------"<<endl
			<<"\t\t\t\t\t|	Passport Management System	|"<<endl
			<<"\t\t\t\t\t-----------------------------------------"<<endl
			<<"\t\t\t\t\t|		Admin Panel		|"<<endl
			<<"\t\t\t\t\t|					|"<<endl;
		
		cout<<"\t\t\t\t\t| Press '1' to see Approved Applicants	|"<<endl
			<<"\t\t\t\t\t| Press '2' to Search Applicant		|"<<endl
			<<"\t\t\t\t\t| Press '3' to see Rejected Applicants	|"<<endl
			<<"\t\t\t\t\t| Press '4' to see Pending Applicants	|"<<endl
			<<"\t\t\t\t\t| Press '5' to Logout			|"<<endl
			<<"\t\t\t\t\t|					|"<<endl
			<<"\t\t\t\t\t-----------------------------------------"<<endl;

		if(adminOptionError==true) {
			cout<<"\n\n\t\t\t\t\t*Error: Invalid Choice Number!";
		}

		cout<<"\n\n\t\t\t\t\tEnter your Choice: ";
		cin>>adminPanelChoice;

		if(adminPanelChoice==1) {

			AdminPanelOptions *option1;
			ApprovedApplicants approvedObj;
			option1= &approvedObj;

			option1->applicantsList();

			break;
		}
		else if(adminPanelChoice==2) {
			
			AdminPanelOptions *option2;
			AdminSearch searchObj;
			option2= &searchObj;

			option2->applicantIdInput();

			break;

		}
		else if(adminPanelChoice==3) {

			AdminPanelOptions *option3;
			RejectedApplicants rejectedObj;
			option3= &rejectedObj;

			option3->applicantsList();

			break;
		}
		else if(adminPanelChoice==4) {

			AdminPanelOptions *option4;
			PendingApplicants pendingObj;
			option4= &pendingObj;

			option4->applicantsList();

			break;
		}
		else if(adminPanelChoice==5) {
			system("CLS");
			welcomeMenu();
		}
		else {
			adminOptionError= true;
			continue;
		}

		break;
	}
	

}

int generateID(int minNum, int maxNum) {
	
	srand((unsigned)time(0));
	int id=0;
	id= rand() % maxNum;
	
	if(id<minNum) {
		id= rand() % maxNum + minNum;
	}
	
	return id;
	
}

string spaceToStarac(string words) {
	
	for(int i=0; i<words.length(); i++) {
		if(words[i]==' ') {
			words[i]='*';
		}
	}
	
	return words;
	
}

string staracToSpace(string words) {
	
	for(int i=0; i<words.length(); i++) {
		if(words[i]=='*') {
			words[i]=' ';
		}
	}
	
	return words;
}
