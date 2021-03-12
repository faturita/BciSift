//#include <kfr/testo/testo.hpp>

#include <kfr/base.hpp>
#include <kfr/dft.hpp>
#include <kfr/dsp.hpp>
#include <kfr/io.hpp>

using namespace kfr;

void testdsp()
{
    univector<fbase, 5> a({ 1, 2, 3, 4, 5 });
    univector<fbase, 5> b({ 0.25, 0.5, 1.0, -2.0, 1.5 });
    univector<fbase> c = convolve(a, b);

    for(int i=0;i<c.size();i++)
    {
        printf("%10.8f,",c[i]);
    }

}
