//ref https://youtu.be/VzxSxPi8DV0?si=HVn4vvqBq4jENhAO
void tut2()
{
    double x[5] = {1, 2, 3, 4, 5};
    double y[5] = {1, 4, 9, 16, 25};

    TGraph *gr = new TGraph(5, x, y);

    // gr->SetMarkerStyle(5);
    gr->SetMarkerStyle(kCircle);
    gr->SetMarkerSize(1);

    TCanvas *c1 = new TCanvas();
    gr->Draw("ALP");    // A -> All, L -> Line, P -> point? refers to the markers for data points
                        // Instead of L, we can use C for curves
                        // Instead of P, we can use * -> Mark data points with a star
}