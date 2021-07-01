#pragma once

#include "HybridModel.h"
#include "cvode.h"
#include "sunlinsol_spgmr.h"
#include "sundials_types.h"
#include "nvector_serial.h"
#include <vector>
#include <random>

namespace Gillespy::TauHybrid
{

	struct IntegratorData
	{
		HybridSimulation *simulation;
		std::vector<HybridSpecies> *species_state;
		std::vector<HybridReaction> *reaction_state;

		std::vector<double> concentrations;
		std::vector<int> populations;
		std::vector<double> propensities;

		IntegratorData(HybridSimulation *simulation);
		IntegratorData(HybridSimulation *simulation, int num_species, int num_reactions);
		IntegratorData(IntegratorData &prev_data);
	};

	/* :IntegrationResults:
	 * Organized data structure for accessing the integrator's output vector.
	 * Contents are MUTABLE! Updating the values in any containing pointers
	 *   will be permanently reflected in the integrator's vector.
	 * 
	 * All pointers in the structure point to different regions of the same vector.
	 * N_Vector: [ --- concentrations --- | ---- rxn_offsets ---- ]
	 */
	struct IntegrationResults
	{
		// concentrations: bounded by [0, num_species)
		realtype *concentrations;
		// reactions:      bounded by [num_species, num_species + num_reactions)
		realtype *reactions;
	};

	class Integrator
	{
	private:
		void *cvode_mem;
		N_Vector y0;
		double t0;
		SUNLinearSolver solver;
		int num_species;
		int num_reactions;
	public:
		N_Vector y;
		realtype t;

		/* save_state()
		 * Creates a duplicate copy of the integrator's current solution vector.
		 * Contents of the most recent duplicate will be restored when restore_state() is called.
		 * 
		 * Returns the time value of the integrator's saved state.
		 */
		double save_state();

		/* restore_state()
		 * Loads the most recent duplicated copy of the solution vector.
		 * 
		 * Returns the time value that the integrator was restored to.
		 */
		double restore_state();

		/* refresh_state()
		 * Loads any new changes to the solution vector without changing previous output.
		 * Any new values assigned to the public N_Vector y will be recognized by the integrator.
		 * The current time value remains the same. To change this, modify `t`.
		 */
		void refresh_state();

		IntegrationResults integrate(double *t);
		IntegratorData data;

		Integrator(HybridSimulation *simulation, N_Vector y0, double reltol, double abstol);
		~Integrator();
	};

	struct URNGenerator
	{
	private:
		std::uniform_real_distribution<double> uniform;
		std::mt19937_64 rng;
	public:
		double next();
		URNGenerator();
		URNGenerator(double seed);
	};

	N_Vector init_model_vector(Model &model, URNGenerator urn);

	int rhs(realtype t, N_Vector y, N_Vector ydot, void *user_data);

}
