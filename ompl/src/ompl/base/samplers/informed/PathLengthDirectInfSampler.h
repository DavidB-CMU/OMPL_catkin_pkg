/*********************************************************************
* Software License Agreement (BSD License)
*
*  Copyright (c) 2014, University of Toronto
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of the University of Toronto nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*********************************************************************/

/* Authors: Jonathan Gammell */

#ifndef OMPL_BASE_SAMPLERS_INFORMED_PATH_LENGTH_DIRECT_INFORMED_SAMPLER_
#define OMPL_BASE_SAMPLERS_INFORMED_PATH_LENGTH_DIRECT_INFORMED_SAMPLER_

#include <ompl/config.h>
#if !OMPL_HAVE_EIGEN3
#error The PathLengthDirectInfSampler class uses Eigen3, which was not detected at build time.
#endif

// We inherit from InformedStateSampler
#include "ompl/base/samplers/InformedStateSampler.h"

namespace ompl
{
    namespace base
    {
        /** \brief An informed sampler for problems seeking to minimize path length.

        It focuses the search to the subset of a problem that can improve a current solution, which is a prolate hyperspheroid (PHS)
        (a special type of an hyperellipsoid) and can be sampled directly.
        Doing so considers all homotopy classes that can provide a better solution while guaranteeing a non-zero probability
        of improving a solution regardless of the size of the planning domain, the number of state dimensions, and how close
        the current solution is to the theoretical minimum.
        Currently only implemented for problems with a single goal in R^n (i.e., RealVectorStateSpace), SE(2) (i.e., SE2StateSpace), and SE(3) (i.e., SE3StateSpace).
        Until an initial solution is found, this sampler simply passes-through to a uniform distribution over the entire state space.
        @par J D. Gammell, S. S. Srinivasa, T. D. Barfoot, "Informed RRT*: Optimal Sampling-based
        Path Planning Focused via Direct Sampling of an Admissible Ellipsoidal Heuristic."
        IROS 2014. DOI: <a href="http://dx.doi.org/10.1109/IROS.2014.6942976">10.1109/IROS.2014.6942976</a>.
        <a href="http://www.youtube.com/watch?v=d7dX5MvDYTc">Illustration video</a>.
        <a href="http://www.youtube.com/watch?v=nsl-5MZfwu4">Short description video</a>.

        \todo
        - Handle other types of goals? */
        class PathLengthDirectInfSampler : public InformedSampler
        {
        public:

            /** \brief Construct a sampler that only generates states with a heuristic solution estimate that is less than the cost of the current solution using a direct ellipsoidal method. */
            PathLengthDirectInfSampler(const ProblemDefinitionPtr probDefn, unsigned int maxNumberCalls);
            virtual ~PathLengthDirectInfSampler();

            /** \brief Sample uniformly in the subset of the state space whose heuristic solution estimates are less than the provided cost. */
            bool sampleUniform(State *statePtr, const Cost &maxCost);

            /** \brief Sample uniformly in the subset of the state space whose heuristic solution estimates are between the provided costs. */
            bool sampleUniform(State *statePtr, const Cost &minCost, const Cost &maxCost);

            /** \brief Whether the sampler can provide a measure of the informed subset */
            bool hasInformedMeasure() const;

            /** \brief The measure of the subset of the state space defined by the current solution cost that is being searched. Does not consider problem boundaries but returns the measure of the entire space if no solution has been found. */
            virtual double getInformedMeasure(const Cost &currentCost) const;

            /** \brief A helper function to calculate the heuristic estimate of the solution cost for the informed subset of a given state. */
            virtual Cost heuristicSolnCost(const State *statePtr) const;

        private:
            // Helper functions:
            /** \brief Sample uniformly in the subset of the state space whose heuristic solution estimates are less than the provided cost using a persistent iteration counter */
            bool sampleUniform(State *statePtr, const Cost &maxCost, unsigned int *iterPtr);

            /** \brief Sample uniformly in the subset of the \e infinite state space whose heuristic solution estimates are less than the provided cost, i.e., ignores the bounds of the state space. */
            void sampleUniformIgnoreBounds(State *statePtr, const Cost &maxCost);

            /** \brief Sample uniformly in the subset of the \e infinite state space whose heuristic solution estimates are between the provided costs, i.e., ignores the bounds of the state space. */
            void sampleUniformIgnoreBounds(State *statePtr, const Cost &minCost, const Cost &maxCost);

            // Variables
            /** \brief The prolate hyperspheroid description of the sub problem */
            ompl::ProlateHyperspheroidPtr phsPtr_;

            /** \brief The index of the subspace of a compound StateSpace for which we can do informed sampling. Unused if the StateSpace is not compound. */
            unsigned int informedIdx_;

            /** \brief The state space of the planning problem that is informed by the heuristics, i.e., in SE(2), R^2*/
            StateSpacePtr informedSubSpace_;

            /** \brief The index of the subspace of a compound StateSpace for which we cannot do informed sampling. Unused if the StateSpace is not compound. */
            unsigned int uninformedIdx_;

            /** \brief The state space of the planning problem that is \e not informed by the heuristics, i.e., in SE(2), SO(2)*/
            StateSpacePtr uninformedSubSpace_;

            /** \brief A regular sampler for the entire statespace for cases where informed sampling cannot be used or is not helpful. I.e., Before a solution is found, or if the solution does not reduce the search space. */
            StateSamplerPtr baseSampler_;

            /** \brief A regular sampler to use on the uninformed subspace. */
            StateSamplerPtr uninformedSubSampler_;

            /** \brief An instance of a random number generator */
            RNG rng_;
        }; // PathLengthDirectInfSampler
    }
}


#endif // OMPL_BASE_SAMPLERS_INFORMED_DIRECT_PATH_LENGTH_INFORMED_SAMPLER_
