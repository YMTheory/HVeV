#include "GlobalDataManager.hh"

#include "globals.hh"
#include <iostream>

// Definition of the static member variable
GlobalDataManager* GlobalDataManager::instance = nullptr;

GlobalDataManager::GlobalDataManager() 
: li7_track_id(-1)
, n_li7_recoil_phonon(0) 
, Etot_li7_recoil_phonon(0)
{
    // Constructor implementation
}

GlobalDataManager::~GlobalDataManager() {
    // Clean up the singleton instance
    if (instance) {
        delete instance;
        instance = nullptr;
    }
}

GlobalDataManager* GlobalDataManager::GetInstance() {
    if (!instance) {
        instance = new GlobalDataManager();
    }
    return instance;
}

int GlobalDataManager::GetLi7RecoilPhononNumber() const
{
    return n_li7_recoil_phonon;
}

void GlobalDataManager::AddOnePhonon()
{
    n_li7_recoil_phonon += 1;
}

int GlobalDataManager::GetLi7RecoilTrackID() const
{
    return li7_track_id;
}

void GlobalDataManager::SetLi7TrackID(int trackid)
{
    li7_track_id = trackid;
}

void GlobalDataManager::AddLi7RecoilPhononEnergy(double E)
{
    Etot_li7_recoil_phonon += E;
}

double GlobalDataManager::GetLi7RecoilPhononEnergy() const
{
    return Etot_li7_recoil_phonon;
}


void GlobalDataManager::ResetVariables()
{
    li7_track_id = -1;
    n_li7_recoil_phonon = 0;
    Etot_li7_recoil_phonon = 0;
}