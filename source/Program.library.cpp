/** 
 * Entry point to an operating system main program.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2018, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "Program.hpp"

#include "library.Align.hpp"
#include "library.Buffer.hpp"

namespace local
{
    using namespace library;

    /**
     * Tests the Align class interface.
     */
    template<typename T>
    bool testAlign(const T& illegal)
    {
        Align<T> o1(5U);
        Align<T> o2(o1);
        Align<T> o3;        
        if( o2.equal(o1) || o2 == o3 || o1 != o2 )
        {
            if( o3.equal(7) )
            {
                o3 = 15;
            }
            o2 = o3;
        }
        bool res;
        const T v = o1;
        if( v == illegal )
        {
            res = false;
        }
        else
        {
            res = true;
        }
        return res;
    }
    
    /**
     * Tests the Buffer class interface.
     */
    template<typename T>
    T testIllegalValue(api::IllegalValue<T>* const obj, const T& val)
    {
        if( not obj->isIllegal(val) )
        {
            obj->setIllegal(val);            
        }
        return obj->getIllegal();
    }
    
    /**
     * Tests the Buffer class interface.
     */
    template<typename T>
    bool testBuffer(const T& illegal)
    {
        bool result = true;        
        // Static buffer class        
        const Buffer<T,7> bs0;         
        Buffer<T,5> bs1(illegal);
        
        #ifdef EOOS_NO_STRICT_MISRA_RULES
        // Dynamic buffer class
        T buf[7];               
        const Buffer<T,0> bd0(7);
        const Buffer<T,0> bd1(7, illegal);        
        const Buffer<T,0> bd2(7, buf);
        const Buffer<T,0> bd3(7, buf, illegal);        
        if( not bd0.isConstructed() )
        {
            result = false;
        }          
        #endif // EOOS_NO_STRICT_MISRA_RULES
        
        if( not bs0.isConstructed() )
        {
            result = false;
        }
        if( bs0.getLength() != 7 )
        {
            result = false;            
        }
        if( bs0.isEmpty() )
        {
            result = false;            
        }        
         
        // Test IllegalValue
        if( result )
        {
            const T ill = testIllegalValue<T>(&bs1, 3);
            if(ill == illegal)
            {
                result = true;
            }
            else
            {
                result = false;
            }
        }
                
        const T element = bs1[2];
                
        bs1.fill(element);                            
        
        return result;
    }
    

    /**
     * Starts executing an operating system main program.
     *
     * "library.Align.hpp"
     * "library.Buffer.hpp"
     * "library.CircularList.hpp"
     * "library.Heap.hpp"
     * "library.LinkedList.hpp"
     * "library.Memory.hpp"
     * "library.Stack.hpp"
     * "library.String.hpp"
     * "library.Toggle.hpp"
     *
     * @return zero, or error code if an error has been occurred.
     */   
    int32 Program::start()
    {  
        int32 error = 0;      
        // Test the Align interface
        if( testAlign<uint32>(7U) == false )
        {
            error = -1;
        }
        // Test the Buffer interface            
        if(error == 0)
        {
            if( testBuffer<int32>(-1) == false )
            {
                error = -2;
            }
        }        
        return error;
    }
}
    
