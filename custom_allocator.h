#include <vector>
#include <tuple>
#include <memory>


struct MemoryPool
{
    struct Deleter
    {
        void operator()(void * p)
        {
            std::free(p);
        }
    };

    using Pointer = std::unique_ptr<void, Deleter>;
    using Element = std::tuple< std::size_t, std::size_t, Pointer>;

    const std::size_t max_number_of_elements;
    std::vector<Element> memory_pool;


    MemoryPool(std::size_t max_number_of_elements_):
        max_number_of_elements{ max_number_of_elements_ }
    {}

    void * pop(std::size_t requested_size)
    {
        if (!memory_pool.empty()) {
            auto & [max_size, size, p] = memory_pool.back();
            if (max_size - size >= requested_size) {
                auto rp = static_cast<char *>(p.get());
                rp += size;
                size += requested_size;

                return static_cast<void *>(rp);
            }
        }

        auto max_size = max_number_of_elements * requested_size;
        auto p = Pointer(std::malloc(max_size), Deleter());
        auto rp = p.get();

        memory_pool.push_back(Element(max_size, requested_size, std::move(p)));

        return rp;
    }
};


template <class T>
struct CustomAllocator
{
    using value_type = T;

    std::shared_ptr<MemoryPool> pool;

    template<class U>
    struct rebind { using other = CustomAllocator<U>; };


    CustomAllocator(std::size_t n):
        pool{ std::make_shared<MemoryPool>(n) }
    {}


    CustomAllocator(const CustomAllocator & other) noexcept:
        pool{ other.pool }
    {}

    template<class U>
    CustomAllocator(const CustomAllocator<U> & other) noexcept:
        pool{ other.pool }
    {}


    CustomAllocator(CustomAllocator && other) noexcept:
        pool{ other.pool }
    {}


    T * allocate(std::size_t n)
    {
        auto p = pool->pop(sizeof(T));
        return static_cast<T *>(p);
    }


    void deallocate(T * p, std::size_t n) noexcept
    {}
};


template <class T, class U>
constexpr bool operator== (
    const CustomAllocator<T> &,
    const CustomAllocator<U> &) noexcept { return true; }

template <class T, class U>
constexpr bool operator != (
    const CustomAllocator<T> &,
    const CustomAllocator<U> &) noexcept { return false; }