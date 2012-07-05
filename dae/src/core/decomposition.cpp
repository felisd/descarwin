#include <sstream>
#include <iomanip>

#include "decomposition.h"
#include "goal.h"

#include "utils/eoJsonUtils.h"

namespace daex
{

  void Decomposition::invalidate() 
 {   this->EO<eoMinimizingFitness>::invalidate();

    //clear the sub_plans vector
    //because if the decomposition becomes invalid, so are its intermediate plans
    this->plans_sub_reset();

    //plan vide
   this->_plan_global = daex::Plan();

 }

void Decomposition::plan_global( daex::Plan p )
{
    _plan_global = p;
}

void Decomposition::plans_sub_add( daex::Plan p ) 
{
    _plans_sub.push_back( p );
}

void Decomposition::plans_sub_reset()
{
    _plans_sub.clear();

    // on prévoit un sous-plan de plus que le nombre de stations
    // pour la dernière étape
    _plans_sub.reserve( this->size() + 1 );
}

void Decomposition::readFrom( std::istream & is )
{
    eoserial::readFrom( *this, is );
}

void Decomposition::printOn( std::ostream & out ) const
{
    eoserial::printOn( *this, out );
}

Decomposition::iterator Decomposition::iter_at( unsigned int i )
{
    if( i >= this->size() ) {
        std::ostringstream msg;
        msg << "asked for element " << i << " but size of the Decomposition is " << this->size();
        throw( std::out_of_range( msg.str() ) );
    }

    Decomposition::iterator it = this->begin();

    std::advance( it, i );
    /*
    for( unsigned int j=0; j < i; ++i  ) {
            ++it;
    }
    */

    return it;
}

void simplePrint( std::ostream & out, Decomposition & decompo )
{
    out << "Decomposition " 
        << std::right << std::setfill(' ') << std::setw(3) 
        << "[" << decompo.size() << "]: ";

    for( Decomposition::iterator igoal = decompo.begin(), end = decompo.end(); igoal != end; ++igoal ) {
        out << "\t" << std::right << std::setfill(' ') << std::setw(3)
            << igoal->earliest_start_time() << "(" << igoal->size() << ")";
    }

    out << std::endl;
}

} // namespace daex

