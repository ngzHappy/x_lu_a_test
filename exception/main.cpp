#include "MainWindow.hpp"
#include <QtWidgets/QApplication>

#include <string>
#include <type_traits>

#include <string>
#include <exception>
#include <stdexcept>

#include<locale>

void exception_handle_detail()noexcept(true);

void excetpion_handle_std(const std::exception &arg) noexcept(true){
    try {

        std::rethrow_if_nested(arg);
    }
    catch (...) {
        exception_handle_detail();
    }
}

void exception_handle_unknow() {

    try {

    }
    catch (...) {
    }

}

void exception_handle_detail()noexcept(true) {
    try {
        std::rethrow_exception(std::current_exception());
    }
    catch (...) {
        exception_handle_unknow();
    }
}

void exception_handle(
    const std::string &argWhere,
    const std::string &argWhat
)noexcept(true) {
    exception_handle_detail();
}

void xfoo() {}

void(*foo)()noexcept(true);

void xjjjd()throw( int ){}

#include<iostream>

void x__() {

    try {
        throw int(12);
    }
    catch (...) {

        try {
            std::throw_with_nested(double(12));
        }
        catch (...) {
            try {
                std::rethrow_if_nested(std::current_exception());
                std::cout<<"x"<<std::endl;
            }
            catch ( const int & ) {
                std::cout<<"int"<<std::endl;
            }
            catch (const double &) {
                std::cout<<"double"<<std::endl;
            }
        }

    }

}

#include<cpp_lua.hpp>

typedef  void(*ExceptionHandleType)(void) ;
ExceptionHandleType get_exception_handle() { return nullptr; }
void set_exception_handle(ExceptionHandleType) {}

void xee() noexcept(true){}
void stt() {
    ExceptionHandleType h=&xee;
}

/*
std::bad_alloc
lua_exception
*/
void exception_handle() noexcept(false) {
    try {
        std::rethrow_exception(std::current_exception());
    }
    catch (const std::bad_alloc&e) { throw e; }
    catch (const lua_ExceptionType*e) { throw e; }
    catch (...) {
        get_exception_handle()();
    }
}

void txxt()  noexcept( noexcept(exception_handle()) ) {}
#include<sstream>
class MStreamBuffer :
    public std::basic_streambuf<char>{
};

//#include <boost/interprocess/streams/bufferstream.hpp>

#include "bufferstream.hpp"

namespace vtest {
//!A streambuf class that controls the transmission of elements to and from
//!a basic_ivectorstream, basic_ovectorstream or basic_vectorstream.
//!It holds a character vector specified by CharVector template parameter
//!as its formatting buffer. The vector must have contiguous storage, like
//!std::vector, boost::interprocess::vector or boost::interprocess::basic_string
template <class CharVector,class CharTraits>
class basic_vectorbuf
    : public std::basic_streambuf<typename CharVector::value_type,CharTraits> {
public:
    typedef CharVector                        vector_type;
    typedef typename CharVector::value_type   char_type;
    typedef typename CharTraits::int_type     int_type;
    typedef typename CharTraits::pos_type     pos_type;
    typedef typename CharTraits::off_type     off_type;
    typedef CharTraits                        traits_type;

//#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
private:
    typedef std::basic_streambuf<char_type,traits_type> base_t;

    basic_vectorbuf(const basic_vectorbuf&);
    basic_vectorbuf & operator =(const basic_vectorbuf&);
//#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

public:

    using base_t::epptr;
    using base_t::pptr;
    using base_t::pbase;

    //!Constructor. Throws if vector_type default
    //!constructor throws.
    explicit basic_vectorbuf(std::ios_base::openmode mode
        =std::ios_base::in|std::ios_base::out)
        : base_t(),m_mode(mode) {
        this->initialize_pointers();
    }

    //!Constructor. Throws if
    //!vector_type(const VectorParameter &param) throws.
    template<class VectorParameter>
    explicit basic_vectorbuf(const VectorParameter &param,
        std::ios_base::openmode mode
        =std::ios_base::in|std::ios_base::out)
        : base_t(),m_mode(mode),m_vect(param) {
        this->initialize_pointers();
    }

public:

    //!Swaps the underlying vector with the passed vector.
    //!This function resets the read/write position in the stream.
    //!Does not throw.
    void swap_vector(vector_type &vect) {
        if (this->m_mode & std::ios_base::out) {
            //Update high water if necessary
            //And resize vector to remove extra size
            if (mp_high_water<base_t::pptr()) {
                //Restore the vector's size if necessary
                mp_high_water=base_t::pptr();
            }
            //This does not reallocate
            m_vect.resize(mp_high_water-(m_vect.size()?&m_vect[0]:0));
        }
        //Now swap vector
        m_vect.swap(vect);
        this->initialize_pointers();
    }

    //!Returns a const reference to the internal vector.
    //!Does not throw.
    const vector_type &vector() const {
        if (this->m_mode & std::ios_base::out) {
            if (mp_high_water<base_t::pptr()) {
                //Restore the vector's size if necessary
                mp_high_water=base_t::pptr();
            }
            //This shouldn't reallocate
            typedef typename vector_type::size_type size_type;
            char_type *old_ptr=base_t::pbase();
            size_type high_pos=size_type(mp_high_water-old_ptr);
            if (m_vect.size()>high_pos) {
                m_vect.resize(high_pos);
                //But we must update end write pointer because vector size is now shorter
                int old_pos=base_t::pptr()-base_t::pbase();
                const_cast<basic_vectorbuf*>(this)->base_t::setp(old_ptr,old_ptr+high_pos);
                const_cast<basic_vectorbuf*>(this)->base_t::pbump(old_pos);
            }
        }
        return m_vect;
    }

    //!Preallocates memory from the internal vector.
    //!Resets the stream to the first position.
    //!Throws if the internals vector's memory allocation throws.
    void reserve(typename vector_type::size_type size) {
        if (this->m_mode & std::ios_base::out && size>m_vect.size()) {
            typename vector_type::difference_type write_pos=base_t::pptr()-base_t::pbase();
            typename vector_type::difference_type read_pos=base_t::gptr()-base_t::eback();
            //Now update pointer data
            m_vect.reserve(size);
            this->initialize_pointers();
            base_t::pbump((int)write_pos);
            if (this->m_mode & std::ios_base::in) {
                base_t::gbump((int)read_pos);
            }
        }
    }

    //!Calls clear() method of the internal vector.
    //!Resets the stream to the first position.
    void clear() { m_vect.clear();   this->initialize_pointers(); }

//#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
private:
    //Maximizes high watermark to the initial vector size,
    //initializes read and write iostream buffers to the capacity
    //and resets stream positions
    void initialize_pointers() {
        // The initial read position is the beginning of the vector.
        if (!(m_mode & std::ios_base::out)) {
            if (m_vect.empty()) {
                this->setg(0,0,0);
            }
            else {
                this->setg(&m_vect[0],&m_vect[0],&m_vect[0]+m_vect.size());
            }
        }

        // The initial write position is the beginning of the vector.
        if (m_mode & std::ios_base::out) {
            //First get real size
            int real_size=(int)m_vect.size();
            //Then maximize size for high watermarking
            m_vect.resize(m_vect.capacity());
//            BOOST_ASSERT(m_vect.size()==m_vect.capacity());
            //Set high watermarking with the expanded size
            mp_high_water=m_vect.size()?(&m_vect[0]+real_size):0;
            //Now set formatting pointers
            if (m_vect.empty()) {
                this->setp(0,0);
                if (m_mode & std::ios_base::in)
                    this->setg(0,0,0);
            }
            else {
                char_type *p=&m_vect[0];
                this->setp(p,p+m_vect.size());
                if (m_mode & std::ios_base::in)
                    this->setg(p,p,p+real_size);
            }
            if (m_mode & (std::ios_base::app|std::ios_base::ate)) {
                base_t::pbump((int)real_size);
            }
        }
    }

protected:
    virtual int_type underflow() {
        if (base_t::gptr()==0)
            return CharTraits::eof();
        if (m_mode & std::ios_base::out) {
            if (mp_high_water<base_t::pptr())
                mp_high_water=base_t::pptr();
            if (base_t::egptr()<mp_high_water)
                base_t::setg(base_t::eback(),base_t::gptr(),mp_high_water);
        }
        if (base_t::gptr()<base_t::egptr())
            return CharTraits::to_int_type(*base_t::gptr());
        return CharTraits::eof();
    }

    virtual int_type pbackfail(int_type c=CharTraits::eof()) {
        if (this->gptr()!=this->eback()) {
            if (!CharTraits::eq_int_type(c,CharTraits::eof())) {
                if (CharTraits::eq(CharTraits::to_char_type(c),this->gptr()[-1])) {
                    this->gbump(-1);
                    return c;
                }
                else if (m_mode & std::ios_base::out) {
                    this->gbump(-1);
                    *this->gptr()=c;
                    return c;
                }
                else
                    return CharTraits::eof();
            }
            else {
                this->gbump(-1);
                return CharTraits::not_eof(c);
            }
        }
        else
            return CharTraits::eof();
    }

    virtual int_type overflow(int_type c=CharTraits::eof()) {
        if (m_mode & std::ios_base::out) {
            if (!CharTraits::eq_int_type(c,CharTraits::eof())) {
                typedef typename vector_type::difference_type dif_t;
                //The new output position is the previous one plus one
                //because 'overflow' requires putting 'c' on the buffer
                dif_t new_outpos=base_t::pptr()-base_t::pbase()+1;
                //Adjust high water if necessary
                dif_t hipos=mp_high_water-base_t::pbase();
                if (hipos<new_outpos)
                    hipos=new_outpos;
                //Insert the new data
                m_vect.push_back(CharTraits::to_char_type(c));
                m_vect.resize(m_vect.capacity());
//                BOOST_ASSERT(m_vect.size()==m_vect.capacity());
                char_type* p=const_cast<char_type*>(&m_vect[0]);
                //A reallocation might have happened, update pointers
                base_t::setp(p,p+(dif_t)m_vect.size());
                mp_high_water=p+hipos;
                if (m_mode & std::ios_base::in)
                    base_t::setg(p,p+(base_t::gptr()-base_t::eback()),mp_high_water);
                //Update write position to the old position + 1
                base_t::pbump((int)new_outpos);
                return c;
            }
            else  // c is EOF, so we don't have to do anything
                return CharTraits::not_eof(c);
        }
        else     // Overflow always fails if it's read-only.
            return CharTraits::eof();
    }

    virtual pos_type seekoff(off_type off,std::ios_base::seekdir dir,
        std::ios_base::openmode mode
        =std::ios_base::in|std::ios_base::out) {
        //Get seek mode
        bool in(0!=(mode & std::ios_base::in)),out(0!=(mode & std::ios_base::out));
        //Test for logic errors
        if (!in&!out)
            return pos_type(off_type(-1));
        else if ((in && out)&&(dir==std::ios_base::cur))
            return pos_type(off_type(-1));
        else if ((in&&(!(m_mode & std::ios_base::in)||(off!=0&&this->gptr()==0)))||
            (out&&(!(m_mode & std::ios_base::out)||(off!=0&&this->pptr()==0))))
            return pos_type(off_type(-1));

        off_type newoff;
        //Just calculate the end of the stream. If the stream is read-only
        //the limit is the size of the vector. Otherwise, the high water mark
        //will mark the real size.
        off_type limit;
        if (m_mode & std::ios_base::out) {
            //Update high water marking because pptr() is going to change and it might
            //have been updated since last overflow()
            if (mp_high_water<base_t::pptr())
                mp_high_water=base_t::pptr();
            //Update read limits in case high water mark was changed
            if (m_mode & std::ios_base::in) {
                if (base_t::egptr()<mp_high_water)
                    base_t::setg(base_t::eback(),base_t::gptr(),mp_high_water);
            }
            limit=static_cast<off_type>(mp_high_water-base_t::pbase());
        }
        else {
            limit=static_cast<off_type>(m_vect.size());
        }

        switch (dir) {
            case std::ios_base::beg:
                newoff=0;
                break;
            case std::ios_base::end:
                newoff=limit;
                break;
            case std::ios_base::cur:
                newoff=in?static_cast<std::streamoff>(this->gptr()-this->eback())
                    :static_cast<std::streamoff>(this->pptr()-this->pbase());
                break;
            default:
                return pos_type(off_type(-1));
        }

        newoff+=off;

        if (newoff < 0||newoff > limit)
            return pos_type(-1);
        if (m_mode & std::ios_base::app && mode & std::ios_base::out && newoff!=limit)
            return pos_type(-1);
        //This can reassign pointers
        //if(m_vect.size() != m_vect.capacity())
        //this->initialize_pointers();
        if (in)
            base_t::setg(base_t::eback(),base_t::eback()+newoff,base_t::egptr());
        if (out) {
            base_t::setp(base_t::pbase(),base_t::epptr());
            base_t::pbump(newoff);
        }
        return pos_type(newoff);
    }

    virtual pos_type seekpos(pos_type pos,std::ios_base::openmode mode
        =std::ios_base::in|std::ios_base::out) {
        return seekoff(pos-pos_type(off_type(0)),std::ios_base::beg,mode);
    }

private:
    std::ios_base::openmode m_mode;
    mutable vector_type     m_vect;
    mutable char_type*      mp_high_water;
//#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

typedef basic_vectorbuf<std::string,std::char_traits<char> > vectorbuf;

}

class StringBuffer :public std::basic_streambuf<char,std::char_traits<char>>{
    using _base_type_=std::basic_streambuf<char,std::char_traits<char>>;
public:
    using _base_type_::epptr;
    using _base_type_::pptr;
    using _base_type_::pbase;
};

void xxe() {

const static std::locale varCLocal{"C"};
    std::stringstream xx ;
    xx.imbue(varCLocal);
    xx.precision(16);

    xx<<1234.567;

    std::cout<<xx.rdbuf()<<std::endl;
    xx.seekp(0,std::ios::end);
    std::cout<< xx.tellp() <<std::endl;
    //reinterpret_cast<StringBuffer*>(xx.rdbuf());

}



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    xxe();
    //foo=&xfoo;



    enum xxt {
        x=noexcept( exception_handle() )
    };
    

    std::char_traits<char>::to_int_type('c');
    std::make_unsigned_t<char> s;

    MainWindow window;
    window.show();

    return app.exec();
}









