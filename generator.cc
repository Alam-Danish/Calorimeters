#include "generator.hh"


MyPrimaryGenerator::MyPrimaryGenerator()
{
    fParticleGun  = new G4ParticleGun(1);

    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName;
    
    electron = particleTable->FindParticle(particleName="e-");
    Muon = particleTable->FindParticle(particleName="mu-");
    Pion = particleTable->FindParticle(particleName="pi-");

    // Default particle
    fParticleGun->SetParticleDefinition(Pion);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{   
    G4ParticleDefinition* particle;
    
    if (fRandomizePrimary)
    {
        G4int i = (int)(3.*G4UniformRand());
        switch(i)
        {
            case 0:
                particle = electron;
                break;
            case 1:
                particle = Muon;
                break;
            default:
                particle = Pion;
                break;
        }
        fParticleGun->SetParticleDefinition(particle);
    }
    else
    {
        particle = fParticleGun->GetParticleDefinition();
    }

    G4cout << "Particle: " << particle->GetParticleName() << G4endl;
    
    G4ThreeVector pos(0., 0., 0.); // origin of the particle gun
    G4ThreeVector mom(0., 0., 1.); // direction of the particle gun

    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);

    G4double Momentum = 10.*GeV;
    G4double SigmaMomentum = 50.*MeV;

    G4double pp = Momentum + (G4UniformRand()-0.5)*SigmaMomentum;
    G4double mass = particle->GetPDGMass();
    G4double Ekin = std::sqrt(pp*pp+mass*mass)-mass;
    fParticleGun->SetParticleEnergy(Ekin);
    
    fParticleGun->GeneratePrimaryVertex(anEvent);
}