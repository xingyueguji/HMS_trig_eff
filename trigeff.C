#include <iostream>
#include <iomanip>
#include <fstream>
#include "TPaveLabel.h"
#include "TH2F.h"
#include "TCanvas.h"

TString filename;

Double_t readhodoeff(Int_t runnum){
	TString froot;
	string word;
	ifstream file;
	Double_t result;
	froot = Form("/net/cdaq/cdaql4data/cdaq/hallc-online-nps2023/REPORT_OUTPUT/COIN/SKIM/skim_NPS_HMS_report_%d_0_1_-1.report",runnum);
	file.open(froot);
	if(file.is_open()==1){
		while (file >> word){
			if (word == "3_of_4"){
				file >> word;
				if (word == "EFF"){
					file >> word >> result;
					break;
				}
			}
		}
	}
	else{
		cout << "Run " << runnum << " is not found!" << endl;
		return -1;
	}
return result;
}

Double_t getpreshlo(Int_t runnum){
	cout << runnum << endl;
	TFile *file = new TFile(filename);
	cout << filename << endl;
  if (file->IsOpen()!=1){
	cout << "ROOTfiles " << runnum << " Not FOUND!" << endl;
    return -1;
  }
  TTree *tdata = (TTree*) file->Get("T");
  if (!tdata){
	cout << "T Tree not found For " << runnum << " !"<< endl;
    return -1;
  }
  tdata->SetBranchStatus("*",0);
  tdata->SetBranchStatus("T.hms.hPRLO_tdcTimeRaw", 1);
  tdata->SetBranchStatus("H.cal.eprtracknorm", 1);
  tdata->SetBranchStatus("T.hms.hEDTM_tdcTime", 1);
  tdata->SetBranchStatus("H.gtr.dp",1);

  Double_t prlo,prshtrk,edtm,delta;
  tdata->SetBranchAddress("T.hms.hPRLO_tdcTimeRaw", &prlo); 
  tdata->SetBranchAddress("H.cal.eprtracknorm", &prshtrk);
  tdata->SetBranchAddress("T.hms.hEDTM_tdcTime", &edtm);
  tdata->SetBranchAddress("H.gtr.dp", &delta);

  Double_t prlocounter = 0;
  Double_t precounter = 0;

  Int_t nentries = tdata->GetEntries();

  for(Int_t i = 0; i < nentries; i++ ){
	if (delta > -9. && delta < 9.){
		if (prlo>0 && edtm == 0) prlocounter++;
		if (prshtrk > 0 && edtm == 0) precounter++;
	}
  }

  return (prlocounter / precounter) * 100;
  delete file;

}

Double_t getcer(Int_t runnum){
	TFile *file = new TFile(filename);
  if (file->IsOpen()!=1){
	cout << "ROOTfiles " << runnum << " Not FOUND!" << endl;
    return -1;
  }
  TTree *tdata = (TTree*) file->Get("T");
  if (!tdata){
	cout << "T Tree not found For " << runnum << " !"<< endl;
    return -1;
  }
  tdata->SetBranchStatus("*",0);
  tdata->SetBranchStatus("T.hms.hCER_tdcTimeRaw", 1);
  tdata->SetBranchStatus("H.cer.npeSum", 1);
  tdata->SetBranchStatus("T.hms.hEDTM_tdcTime", 1);
  tdata->SetBranchStatus("H.gtr.dp",1);

  Double_t npeSum,certdc,edtm,delta;
  tdata->SetBranchAddress("T.hms.hCER_tdcTimeRaw", &certdc); 
  tdata->SetBranchAddress("H.cer.npeSum", &npeSum);
  tdata->SetBranchAddress("T.hms.hEDTM_tdcTime", &edtm);
  tdata->SetBranchAddress("H.gtr.dp", &delta);

  Double_t certdccounter = 0;
  Double_t cercounter = 0;

  Int_t nentries = tdata->GetEntries();

  for(Int_t i = 0; i < nentries; i++ ){
	if (delta > -9. && delta < 9.){
		if (certdc>0 && edtm == 0) certdccounter++;
		if (npeSum>0 && edtm == 0) cercounter++;
	}
  }

  return (certdccounter / cercounter) * 100;
  delete file;

}

Double_t getshlo(Int_t runnum){
	TFile *file = new TFile(filename);
  if (file->IsOpen()!=1){
	cout << "ROOTfiles " << runnum << " Not FOUND!" << endl;
    return -1;
  }
  TTree *tdata = (TTree*) file->Get("T");
  if (!tdata){
	cout << "T Tree not found For " << runnum << " !"<< endl;
    return -1;
  }
  tdata->SetBranchStatus("*",0);
  tdata->SetBranchStatus("T.hms.hSHWR_tdcTimeRaw", 1);
  tdata->SetBranchStatus("H.cal.etottracknorm", 1);
  tdata->SetBranchStatus("T.hms.hEDTM_tdcTime", 1);
  tdata->SetBranchStatus("H.gtr.dp",1);

  Double_t shlo,totshtrk,edtm,delta;
  tdata->SetBranchAddress("T.hms.hSHWR_tdcTimeRaw", &shlo); 
  tdata->SetBranchAddress("H.cal.etottracknorm", &totshtrk);
  tdata->SetBranchAddress("T.hms.hEDTM_tdcTime", &edtm);
  tdata->SetBranchAddress("H.gtr.dp", &delta);

  Double_t shlocounter = 0;
  Double_t etotcounter = 0;

  Int_t nentries = tdata->GetEntries();

  for(Int_t i = 0; i < nentries; i++ ){
	if (delta > -9. && delta < 9.){
		if (shlo>0 && edtm == 0) shlocounter++;
		if (totshtrk > 0 && edtm == 0) etotcounter++;
	}
  }

  return (shlocounter / etotcounter) * 100;
  delete file;

}

Double_t getpreshhi(Int_t runnum){
	TFile *file = new TFile(filename);
  if (file->IsOpen()!=1){
	cout << "ROOTfiles " << runnum << " Not FOUND!" << endl;
    return -1;
  }
  TTree *tdata = (TTree*) file->Get("T");
  if (!tdata){
	cout << "T Tree not found For " << runnum << " !"<< endl;
    return -1;
  }
  tdata->SetBranchStatus("*",0);
  tdata->SetBranchStatus("T.hms.hPRHI_tdcTimeRaw", 1);
  tdata->SetBranchStatus("H.cal.eprtracknorm", 1);
  tdata->SetBranchStatus("T.hms.hEDTM_tdcTime", 1);
  tdata->SetBranchStatus("H.gtr.dp",1);

  Double_t prhi,prshtrk,edtm,delta;
  tdata->SetBranchAddress("T.hms.hPRLO_tdcTimeRaw", &prhi); 
  tdata->SetBranchAddress("H.cal.eprtracknorm", &prshtrk);
  tdata->SetBranchAddress("T.hms.hEDTM_tdcTime", &edtm);
  tdata->SetBranchAddress("H.gtr.dp", &delta);

  Double_t prhicounter = 0;
  Double_t precounter = 0;

  Int_t nentries = tdata->GetEntries();

  for(Int_t i = 0; i < nentries; i++ ){
	if (delta > -9. && delta < 9.){
		if (prhi>0 && edtm == 0) prhicounter++;
		if (prshtrk > 0 && edtm == 0) precounter++;
	}
  }

  return (prhicounter / precounter) * 100;
  delete file;

}


void trigeff(){
	TString runfilename = "efficiency.dat";
	ifstream ifs;
	Int_t runNUM;
	Double_t hodoeff = -1;
	Double_t prloeff = -1;
	Double_t prhieff = -1;
	Double_t shloeff = -1;
	Double_t cereff = -1;
	ofstream ofs;
	ofs.open("trigeff.data");
	ofs << " #!3of4/     prlo/      prhi/      shlo/       cer/      " << endl;

	ifs.open(runfilename);
	string line;
	while (getline(ifs, line)){

		runNUM = stoi(line);
		filename=Form("/net/cdaq/cdaql3data/cdaq/hallc-online-nps2023/ROOTfiles/COIN/SKIM/nps_hms_skim_%d_0_1_-1.root", runNUM);
		hodoeff = readhodoeff(runNUM);
		prloeff = getpreshlo(runNUM);
		prhieff = getpreshhi(runNUM);
		shloeff = getshlo(runNUM);
		cereff = getcer(runNUM);
		if (hodoeff != -1 && prloeff != -1 && prhieff != -1 && shloeff != -1 && cereff != -1) ofs << Form("%i      %f      %f      %f      %f      %f", runNUM, hodoeff, prloeff, prhieff, shloeff, cereff) << endl;

		ofs.close();
	}
}