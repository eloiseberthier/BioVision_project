#pragma once
#include "psc_utils.hpp"
#include "matrice.hpp"

namespace psc_utils
{
    class Kohonen : public Matrice
    {
    private:
        int typeDistance;
        float alpha;
        float voisinage;

    public:
        Kohonen(int numDis, float alphaInit, float r, int timestamp);
        Kohonen(const std::string& namefile, int timestamp);
        Kohonen();
        ~Kohonen();
        Point plusProchePoint(const Vecteur& v) const;
        void randomInit();
        void modifierVoisin(Vecteur v, Point pointProche);
        void changeParam(float deltaAlpha, float deltaR);
        void evolution(Vecteur v, float deltaAlpha, float deltaR);
        void resetMap();
        void resetTempsMap();
        void save(const std::string& namefile) const;
        void print(int layer) const;

       // std::list<Vecteur> voisins(Point& p, int largest_x, int largest_y);

    };
}
