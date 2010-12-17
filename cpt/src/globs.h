/*
 * CPT - a Constraint Programming Temporal planner
 *
 * File : globs.h
 *
 * Copyright (C) 2005-2009  Vincent Vidal <vidal@cril.univ-artois.fr>
 */


#ifndef GLOBS_H
#define GLOBS_h


#include "structs.h"
#include "plan.h"


EVECTOR(Action *, actions);
EVECTOR(Fluent *, fluents);
EVECTOR(Causal *, causals);
EVECTOR(Action *, active_actions);
EVECTOR(Causal *, active_causals);
#ifdef RESOURCES
EVECTOR(Resource *, resources);
#endif
extern long total_actions_nb;

extern Action *start_action;
extern Action *end_action;

EVECTOR(Fluent *, init_state);
EVECTOR(Fluent *, goal_state);

extern SolutionPlan *solution_plan;
EVECTOR(SolutionPlan *, plans);

extern Statistics stats;

extern Causal *last_conflict_candidate;
EVECTOR(Causal *, last_conflicts);


#endif /* GLOBS_H */
