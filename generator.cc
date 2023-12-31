#include "generator.hh"

// Particle generator class
MyPrimaryGenerator::MyPrimaryGenerator()
{
    fParticleGun  = new G4ParticleGun(1); // Create a particle gun with 1 particle

    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName;
    
    // Define the particles to be generated by the gun
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
    
    // Randomize the primary particle type (electron, muon, pion)
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

    // Uncomment the following line to print the particle name on the terminal
    // G4cout << "Particle: " << particle->GetParticleName() << G4endl;
    
    G4ThreeVector pos(0., 0., -2.0*m); // origin of the particle gun
    G4ThreeVector mom(0., 0., 1.); // direction of the particle gun

    fParticleGun->SetParticlePosition(pos); // Position of the particle gun
    fParticleGun->SetParticleMomentumDirection(mom); // Momentum direction of the particle gun

    G4double Momentum = 10.*GeV; // Momentum of the particle gun
    G4double SigmaMomentum = 50.*MeV; // Momentum uncertainity of the particle gun

    G4double pp = Momentum + (G4UniformRand()-0.5)*SigmaMomentum; 
    G4double mass = particle->GetPDGMass(); // Mass of the particle
    G4double Ekin = std::sqrt(pp*pp+mass*mass)-mass; // Kinetic energy of the particle
    fParticleGun->SetParticleEnergy(Ekin); // Energy of the particle gun
    
    fParticleGun->GeneratePrimaryVertex(anEvent); // Generate the primary vertex
}