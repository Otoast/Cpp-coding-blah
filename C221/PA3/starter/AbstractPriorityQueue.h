#ifndef ABSTRACT_PRIORITY_QUEUE_H
#define ABSTRACT_PRIORITY_QUEUE_H

template <typename Type>
class AbstractPriorityQueue {
    public:
        AbstractPriorityQueue() {};
        virtual ~AbstractPriorityQueue() {};
        virtual void pq_insert(Type value) = 0;
        virtual Type pq_delete() = 0;
        virtual int pq_size() = 0;
        virtual Type pq_get_min() = 0;
};

#endif