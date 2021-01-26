#include <memory>


template<class T>
struct Node
{
    T data;
    Node * next{ nullptr };

    template<class ...Args>
    Node(Args&& ...args) noexcept:
        data{ std::forward<Args>(args)... }
    {}
};


template<class T, class Alloc = std::allocator<T>>
class CustomContainer
{
    using type_alloc_traits = std::allocator_traits<Alloc>;
    using node_alloc_traits = typename type_alloc_traits::template rebind_traits<Node<T>>;
    using node_alloc = typename type_alloc_traits::template rebind_alloc<Node<T>>;

public:

    class iterator
    {
    public:
        iterator(Node<T> * ptr): ptr(ptr) {}
        iterator operator++() { ptr = ptr->next; return *this; }
        bool operator!=(const iterator & other) const { return ptr != other.ptr; }
        T & operator*() const { return ptr->data; }
    private:
        Node<T> * ptr;
    };

    CustomContainer(Alloc const & alloc = Alloc{}) :
        _alloc{alloc},
        _first{nullptr},
        _last{nullptr}
    {}

    CustomContainer(const CustomContainer & container) = delete;

    CustomContainer(CustomContainer && container) noexcept:
        _alloc{ std::move(container._alloc) },
        _first{ std::exchange(container._first, nullptr) },
        _last{ std::exchange(container._last, nullptr) }
    {}

    ~CustomContainer()
    {
        while (_first) {
            auto temp = _first;
            _first = _first->next;
            deleteNode(temp);
        }
    }

    template<class ...Args>
    void emplace(Args&& ...args)
    {
        auto new_node = newNode(std::forward<Args>(args)...);

        if (_last) {
            _last->next = new_node;
        }
        else {
            _first = new_node;
        }

        _last = new_node;
    }

    iterator begin() const { return iterator(_first); }
    iterator end() const { return iterator(nullptr); }

private:

    template<class ...Args>
    auto newNode(Args&& ...args) -> Node<T> *
    {
        auto node = node_alloc_traits::allocate(_alloc, 1);
        node_alloc_traits::construct(_alloc, node, std::forward<Args>(args)...);
        return node;
    }

    auto deleteNode(Node<T> * const node) -> void
    {
        node_alloc_traits::destroy(_alloc, node);
        node_alloc_traits::deallocate(_alloc, node, 1);
    }

    node_alloc _alloc;
    Node<T> * _first;
    Node<T> * _last;
};
