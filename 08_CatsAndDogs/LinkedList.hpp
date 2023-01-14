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
                T storage;
            };

        public:
            ~LinkedList()
            {
                Element* next;
                for (Element* element = m_first; element; element = next)
                {
                    next = element->next;
                    delete element;
                }
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
                Element** element = &m_first;
                for(size_t i = 0; i < index; i++)
                {
                    element = &(*element)->next;
                }
                Element* next = (*element)->next;
                delete *element;
                (*element) = next;
                m_count--;
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
                    insertionPosition = &(*insertionPosition)->next;
                }
                *insertionPosition = element;
                m_count++;
            }

        private:
            Element* m_first = nullptr;
            size_t m_count = 0;
    };
}
