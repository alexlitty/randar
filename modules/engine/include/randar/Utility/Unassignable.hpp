#ifndef RANDAR_UTILITY_UNASSIGNABLE_HPP
#define RANDAR_UTILITY_UNASSIGNABLE_HPP

namespace randar
{
    /**
     * A helper object that indicates unassignability.
     *
     * The compiler will complain if an assignment or copy is attempted on the
     * child, unless the child defines its own copy constructor or assignment
     * operator -- In which case, this shouldn't be a parent, you evil kook.
     */
    struct Unassignable
    {
        Unassignable(Unassignable const&) = delete; 
        Unassignable& operator=(Unassignable const&) = delete;
        Unassignable();
    }
}

#endif
