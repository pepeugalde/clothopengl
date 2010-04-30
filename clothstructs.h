/* The particle class represents a particle of mass that can move around in 3D space*/
typedef struct particle{
	bool movable; // can the particle move or not ? used to pin parts of the cloth

	float mass; // the mass of the particle (is always 1 in this example)
	Vec3 pos; // the current position of the particle in 3D space
	Vec3 old_pos; // the position of the particle in the previous time step, used as part of the verlet numerical integration scheme
	Vec3 acceleration; // a vector representing the current acceleration of the particle
	Vec3 accumulated_normal; // an accumulated normal (i.e. non normalized), used for OpenGL soft shading
} particle;


typedef struct constraint{
	float rest_distance; // the length between particle p1 and p2 in rest configuration
	Particle *p1, *p2; // the two particles that are connected through this constraint
} constraint;


typedef struct cloth{
	int num_particles_width; // number of particles in "width" direction
	int num_particles_height; // number of particles in "height" direction
	// total number of particles is num_particles_width*num_particles_height

	std::vector<Particle> particles; // all particles that are part of this cloth
	std::vector<Constraint> constraints; // alle constraints between particles as part of this cloth

	Particle* getParticle(int x, int y) {return &particles[y*num_particles_width + x];}
	void makeConstraint(Particle *p1, Particle *p2) {constraints.push_back(Constraint(p1,p2));}
} cloth;
