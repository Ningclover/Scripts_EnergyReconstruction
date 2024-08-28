void plot_sensitivity(){
	TCanvas *c1 = new TCanvas("c1","c1",800,600);
	TGraph *g[6];
	//int color[] = {kOrange, kGreen, kRed,kBlack ,kBlue,kBlack};
	int color[] = {1,kGreen+2,4,6,2,4,5};
	for(int i=0;i<5;i++){
		if(i==3)continue;
		//g[i] = new TGraph(Form("./dat/dune_dcp_shape_%i.dat",i));
		//g[i] = new TGraph(Form("dat/dune_dcp_1nd_%i.dat",i));
		g[i] = new TGraph(Form("dat/dune_dcp_2nd_%i.dat",i));
		//g[i] = new TGraph(Form("dune_dcp_%i.dat",i));
		//g[i] = new TGraph(Form("dune_hie_%i.dat",i));
		g[i] ->SetLineWidth(2);
		g[i]->SetLineColor(color[i]);
		if(i==0)g[i]->Draw("l A");
		else g[i]->Draw("same l");
		cout<<i<<endl;
	}
	//g[0]->GetYaxis()->SetRangeUser(10,35);
	g[0]->GetYaxis()->SetRangeUser(0,10);
	g[0]->GetXaxis()->SetRangeUser(-180,180);
	g[0]->GetXaxis()->SetTitle("#delta_{CP} #circ");
	g[0]->GetYaxis()->SetTitle("#sqrt{#Delta #chi ^{2}}");
	g[0]->GetXaxis()->CenterTitle();
	g[0]->GetYaxis()->CenterTitle();
	gPad->SetGrid();
	TLegend *leg2 = new TLegend(0.3,0.72, 0.7,0.85);
	leg2->SetNColumns(2);  
	leg2->SetBorderSize(0);
	leg2->AddEntry(g[0], "Q1", "l");
	leg2->AddEntry(g[1], "Q2", "l");
	leg2->AddEntry(g[2], "Q3", "l");
	leg2->AddEntry(g[4], "L1", "l");
	//	leg2->AddEntry(g[5], "MicroBooNE", "l");
	leg2->Draw();
	//c1->SaveAs("plot/CP-sens-1st.pdf");
	c1->SaveAs("plot/CP-sens-2nd.pdf");
	//c1->SaveAs("plot/CP-sens-shape.pdf");
}

void plot_stage(){
	TCanvas *c1 = new TCanvas("c1","c1",800,600);
	TGraph *g[6];
	int color[] = {kOrange, kGreen, kRed,kBlack ,kBlue,kBlack};
	for(int i=0;i<5;i++){
		if(i==3)continue;
		//g[i] = new TGraph(Form("dune_stage_%i.dat",i));
		//g[i] = new TGraph(Form("dune_stage_1nd_%i.dat",i));
		g[i] = new TGraph(Form("dune_stage_shape_%i.dat",i));
		g[i] ->SetLineWidth(3);
		g[i]->SetLineColor(color[i]);
		if(i==0)g[i]->Draw("l A");
		else g[i]->Draw("same l");
	}
	g[0]->GetYaxis()->SetRangeUser(0,20);
	g[0]->GetXaxis()->SetRangeUser(0,15);
	g[0]->GetXaxis()->SetTitle("Years");
	g[0]->GetYaxis()->SetTitle("#sqrt{#Delta #chi ^{2}}");
	TLegend *leg2 = new TLegend(0.65,0.60, 0.87,0.87);
	leg2->SetBorderSize(0);
	leg2->AddEntry(g[0], "M1", "l");
	leg2->AddEntry(g[1], "M2", "l");
	leg2->AddEntry(g[2], "M3", "l");
	leg2->AddEntry(g[4], "Light", "l");
	//	leg2->AddEntry(g[5], "MicroBooNE", "l");
	leg2->Draw();
	//	c1->SaveAs("/Users/xning/code/dual_cal_paper/Pic/dune_stage_shape.pdf");
}
