#pragma once

namespace FuselUtil
{
    template<typename T>
    class LinkedList
    {
        private:
            struct Element
            {
                Element() = delete;
                Element(const T& data) :
                    storage(data)
                {}
                Element(T&& data) :
                    storage(std::move(data))
                {}

                Element* next = nullptr;
                Element* prev = nullptr;
                T storage;
            };

        public:
            class Iterator
            {
                public:
                    Iterator() = default;
                    Iterator(Element* element) :
                        m_element(element)
                    {}

                    inline void Fwd() 
                    {
                        m_element = m_element->next;
                    }
                    inline void Bwd()
                    {
                        m_element = m_element->prev;
                    }
                    inline T& Data()
                    {
                        return m_element->storage;
                    }
                    inline const T& Data() const
                    {
                        return m_element->storage;
                    }

                    T& operator*()
                    {
                        return Data();
                    }
                    const T& operator*() const
                    {
                        return Data();
                    }

                    friend static bool operator==(const Iterator& lhs, const Iterator& rhs)
                    {
                        return lhs.m_element == rhs.m_element;
                    }

                    Iterator& operator++()
                    {
                        Fwd();
                        return *this;
                    }
                    Iterator operator++(int)
                    {
                        auto copy = *this;
                        Fwd();
                        return copy;
                    }

                    Iterator& operator--()
                    {
                        Bwd();
                        return *this;
                    }
                    Iterator operator--(int)
                    {
                        auto copy = *this;
                        Bwd();
                        return copy;
                    }

                private:
                    Element* m_element = nullptr;
            };

        public:
            LinkedList() = default;
            LinkedList(const LinkedList& other)
            {
                for (auto* element = other.m_first; element; element = element->next)
                {
                    Append(element->storage);
                }
            }
            LinkedList(LinkedList&& other) noexcept :
                m_first(other.m_first), m_count(other.m_count)
            {
                other.m_first = nullptr;
                other.m_count = 0;
            }
            ~LinkedList()
            {
                Clear();
            }

            LinkedList& operator=(const LinkedList& other)
            {
                if (this != &other)
                {
                    this->~LinkedList();
                    new(this)LinkedList(other);
                }
                return *this;
            }
            LinkedList& operator=(LinkedList&& other) noexcept
            {
                if (this != &other)
                {
                    this->~LinkedList();
                    new(this)LinkedList(std::move(other));
                }
                return *this;
            }

            void Append(const T& element)
            {
                AppendElement(new Element(element));
            }
            void Append(T&& element)
            {
                AppendElement(new Element(std::move(element)));
            }

            void Erase(size_t index)
            {
                // Seek element
                Element** element = &m_first;
                for(size_t i = 0; i < index; i++)
                {
                    element = &(*element)->next;
                }
                // Getting next pointer
                Element* next = (*element)->next;
                // Fixing backward linking of next element
                if (next)
                {
                    next->prev = (*element)->prev;
                }
                // Deletion of element
                delete *element;
                // Fixing forward linking
                (*element) = next;

                m_count--;
            }

            void Clear()
            {
                Element* next;
                for (Element* element = m_first; element; element = next)
                {
                    next = element->next;
                    delete element;
                }
                m_first = nullptr;
                m_count = 0;
            }

            T& At(size_t index)
            {
                Element* element = m_first;
                for (size_t i = 0; i < index; i++)
                {
                    element = element->next;
                }
                return element->storage;
            }

            const T& At(size_t index) const
            {
                Element* element = m_first;
                for (size_t i = 0; i < index; i++)
                {
                    element = element->next;
                }
                return element->storage;
            }

            inline Iterator begin()
            {
                return Iterator(m_first);
            }
            inline Iterator end()
            {
                return Iterator();
            }

            inline size_t Count() const noexcept
            {
                return m_count;
            }
            
            inline T& operator[](size_t index)
            {
                return At(index);
            }
            inline const T& operator[](size_t index) const
            {
                return At(index);
            }

        private:
            void AppendElement(Element* element)
            {
                Element** insertionPosition = &m_first;
                while (*insertionPosition)
                {
                    element->prev = *insertionPosition;
                    insertionPosition = &(*insertionPosition)->next;
                }
                *insertionPosition = element;
                m_count++;
            }

        private:
            mutable Element* m_first = nullptr;
            size_t m_count = 0;
    };
}
