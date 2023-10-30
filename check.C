void check(){
	TString filename;
	Int_t runNUM = 1709;
	filename=Form("/cache/hallc/c-nps/analysis/online/replays/nps_hms_coin_%d_0_1_-1.root", runNUM);
	TFile *file = new TFile(filename);
}