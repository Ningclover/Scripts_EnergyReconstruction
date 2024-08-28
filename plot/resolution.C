#ifdef __CLING__
#pragma cling optimize(0)
#endif
void resolution()
{
//=========Macro generated from canvas: c1/c1
//=========  (Wed Aug 28 14:42:35 2024) by ROOT version 6.28/06
   TCanvas *c1 = new TCanvas("c1", "c1",76,85,800,600);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c1->Range(-1.15,-4.324324,6.35,22.7027);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetGridx();
   c1->SetGridy();
   c1->SetTickx(1);
   c1->SetTicky(1);
   c1->SetLeftMargin(0.16);
   c1->SetRightMargin(0.12);
   c1->SetBottomMargin(0.16);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1[10] = { 0.5, 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5 };
   Double_t Graph0_fy1[10] = { 7.78258, 5.78834, 5.343876, 4.984401, 4.616562, 4.454771, 4.283524, 4.246414, 4.091021, 3.897034 };
   TGraph *graph = new TGraph(10,Graph0_fx1,Graph0_fy1);
   graph->SetName("Graph0");
   graph->SetTitle("Graph");
   graph->SetFillStyle(1000);
   graph->SetLineColor(4);
   graph->SetLineWidth(2);
   graph->SetMarkerStyle(20);
   graph->SetMarkerSize(0.6);
   
   TH1F *Graph_Graph01 = new TH1F("Graph_Graph01","Graph",100,0.05,5.45);
   Graph_Graph01->SetMinimum(0);
   Graph_Graph01->SetMaximum(20);
   Graph_Graph01->SetDirectory(nullptr);
   Graph_Graph01->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Graph_Graph01->SetLineColor(ci);
   Graph_Graph01->SetLineWidth(2);
   Graph_Graph01->SetMarkerStyle(20);
   Graph_Graph01->SetMarkerSize(0.6);
   Graph_Graph01->GetXaxis()->SetTitle("Energy [GeV]");
   Graph_Graph01->GetXaxis()->CenterTitle(true);
   Graph_Graph01->GetXaxis()->SetLabelFont(132);
   Graph_Graph01->GetXaxis()->SetLabelSize(0.06);
   Graph_Graph01->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph01->GetXaxis()->SetTitleOffset(1.1);
   Graph_Graph01->GetXaxis()->SetTitleFont(132);
   Graph_Graph01->GetYaxis()->SetTitle("Resolution [%]");
   Graph_Graph01->GetYaxis()->CenterTitle(true);
   Graph_Graph01->GetYaxis()->SetLabelFont(132);
   Graph_Graph01->GetYaxis()->SetLabelSize(0.06);
   Graph_Graph01->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph01->GetYaxis()->SetTitleOffset(1.2);
   Graph_Graph01->GetYaxis()->SetTitleFont(132);
   Graph_Graph01->GetZaxis()->SetLabelFont(132);
   Graph_Graph01->GetZaxis()->SetLabelSize(0.06);
   Graph_Graph01->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph01->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01->GetZaxis()->SetTitleFont(132);
   graph->SetHistogram(Graph_Graph01);
   
   graph->Draw("al");
   
   Double_t Graph1_fx2[10] = { 0.5, 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5 };
   Double_t Graph1_fy2[10] = { 9.81404, 11.33571, 10.89328, 9.854855, 9.236902, 8.861025, 8.316676, 8.189959, 7.574486, 6.17943 };
   graph = new TGraph(10,Graph1_fx2,Graph1_fy2);
   graph->SetName("Graph1");
   graph->SetTitle("Graph");
   graph->SetFillStyle(1000);

   ci = TColor::GetColor("#009900");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);
   graph->SetMarkerStyle(20);
   graph->SetMarkerSize(0.6);
   
   TH1F *Graph_Graph12 = new TH1F("Graph_Graph12","Graph",100,0.05,5.45);
   Graph_Graph12->SetMinimum(5.663802);
   Graph_Graph12->SetMaximum(11.85134);
   Graph_Graph12->SetDirectory(nullptr);
   Graph_Graph12->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph12->SetLineColor(ci);
   Graph_Graph12->SetLineWidth(2);
   Graph_Graph12->SetMarkerStyle(20);
   Graph_Graph12->SetMarkerSize(0.6);
   Graph_Graph12->GetXaxis()->SetLabelFont(132);
   Graph_Graph12->GetXaxis()->SetLabelSize(0.06);
   Graph_Graph12->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph12->GetXaxis()->SetTitleOffset(1.1);
   Graph_Graph12->GetXaxis()->SetTitleFont(132);
   Graph_Graph12->GetYaxis()->SetLabelFont(132);
   Graph_Graph12->GetYaxis()->SetLabelSize(0.06);
   Graph_Graph12->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph12->GetYaxis()->SetTitleOffset(1.2);
   Graph_Graph12->GetYaxis()->SetTitleFont(132);
   Graph_Graph12->GetZaxis()->SetLabelFont(132);
   Graph_Graph12->GetZaxis()->SetLabelSize(0.06);
   Graph_Graph12->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph12->GetZaxis()->SetTitleOffset(1);
   Graph_Graph12->GetZaxis()->SetTitleFont(132);
   graph->SetHistogram(Graph_Graph12);
   
   graph->Draw(" l ");
   
   Double_t Graph2_fx3[10] = { 0.5, 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5 };
   Double_t Graph2_fy3[10] = { 12.99836, 13.85539, 14.14634, 13.69805, 13.13573, 12.9998, 12.80928, 12.62441, 12.47708, 12.33069 };
   graph = new TGraph(10,Graph2_fx3,Graph2_fy3);
   graph->SetName("Graph2");
   graph->SetTitle("Graph");
   graph->SetFillStyle(1000);
   graph->SetLineWidth(2);
   graph->SetMarkerStyle(20);
   graph->SetMarkerSize(0.6);
   
   TH1F *Graph_Graph23 = new TH1F("Graph_Graph23","Graph",100,0.05,5.45);
   Graph_Graph23->SetMinimum(12.14912);
   Graph_Graph23->SetMaximum(14.32791);
   Graph_Graph23->SetDirectory(nullptr);
   Graph_Graph23->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph23->SetLineColor(ci);
   Graph_Graph23->SetLineWidth(2);
   Graph_Graph23->SetMarkerStyle(20);
   Graph_Graph23->SetMarkerSize(0.6);
   Graph_Graph23->GetXaxis()->SetLabelFont(132);
   Graph_Graph23->GetXaxis()->SetLabelSize(0.06);
   Graph_Graph23->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph23->GetXaxis()->SetTitleOffset(1.1);
   Graph_Graph23->GetXaxis()->SetTitleFont(132);
   Graph_Graph23->GetYaxis()->SetLabelFont(132);
   Graph_Graph23->GetYaxis()->SetLabelSize(0.06);
   Graph_Graph23->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph23->GetYaxis()->SetTitleOffset(1.2);
   Graph_Graph23->GetYaxis()->SetTitleFont(132);
   Graph_Graph23->GetZaxis()->SetLabelFont(132);
   Graph_Graph23->GetZaxis()->SetLabelSize(0.06);
   Graph_Graph23->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph23->GetZaxis()->SetTitleOffset(1);
   Graph_Graph23->GetZaxis()->SetTitleFont(132);
   graph->SetHistogram(Graph_Graph23);
   
   graph->Draw(" l ");
   
   Double_t Graph3_fx4[10] = { 0.5, 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5 };
   Double_t Graph3_fy4[10] = { 10.64021, 8.550993, 7.207297, 6.238984, 5.608295, 5.065902, 4.731687, 4.423945, 4.141932, 3.826476 };
   graph = new TGraph(10,Graph3_fx4,Graph3_fy4);
   graph->SetName("Graph3");
   graph->SetTitle("Graph");
   graph->SetFillStyle(1000);
   graph->SetLineColor(2);
   graph->SetLineWidth(2);
   graph->SetMarkerStyle(20);
   graph->SetMarkerSize(0.6);
   
   TH1F *Graph_Graph34 = new TH1F("Graph_Graph34","Graph",100,0.05,5.45);
   Graph_Graph34->SetMinimum(3.145103);
   Graph_Graph34->SetMaximum(11.32158);
   Graph_Graph34->SetDirectory(nullptr);
   Graph_Graph34->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph34->SetLineColor(ci);
   Graph_Graph34->SetLineWidth(2);
   Graph_Graph34->SetMarkerStyle(20);
   Graph_Graph34->SetMarkerSize(0.6);
   Graph_Graph34->GetXaxis()->SetLabelFont(132);
   Graph_Graph34->GetXaxis()->SetLabelSize(0.06);
   Graph_Graph34->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph34->GetXaxis()->SetTitleOffset(1.1);
   Graph_Graph34->GetXaxis()->SetTitleFont(132);
   Graph_Graph34->GetYaxis()->SetLabelFont(132);
   Graph_Graph34->GetYaxis()->SetLabelSize(0.06);
   Graph_Graph34->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph34->GetYaxis()->SetTitleOffset(1.2);
   Graph_Graph34->GetYaxis()->SetTitleFont(132);
   Graph_Graph34->GetZaxis()->SetLabelFont(132);
   Graph_Graph34->GetZaxis()->SetLabelSize(0.06);
   Graph_Graph34->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph34->GetZaxis()->SetTitleOffset(1);
   Graph_Graph34->GetZaxis()->SetTitleFont(132);
   graph->SetHistogram(Graph_Graph34);
   
   graph->Draw(" l");
   
   TLegend *leg = new TLegend(0.6,0.7,0.87,0.87,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(133);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("Graph2","Q1","l");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(133);
   entry=leg->AddEntry("Graph1","Q2","l");

   ci = TColor::GetColor("#009900");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(133);
   entry=leg->AddEntry("Graph0","Q3","l");
   entry->SetLineColor(4);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(133);
   entry=leg->AddEntry("Graph3","L1","l");
   entry->SetLineColor(2);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(133);
   leg->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
