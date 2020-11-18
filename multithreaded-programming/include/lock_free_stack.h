#include <atomic>
#include <memory>

#ifndef __LOCK_FREE_STACK_H__
#define __LOCK_FREE_STACK_H__

template<typename T>
class lock_free_stack {
private:
  struct node {
    std::shared_ptr<T> data;
    node* next;
    node(const T& data_) : data(std::make_shared<T>(data_)) {}
  };
  std::atomic<node*> head;
  std::atomic<unsigned> threads_in_pop;
  std::atomic<node*> to_be_deleted;
  static void delete_nodes(node* nodes) {
    while(nodes) {
      node* next = nodes->next;
      delete nodes;
      nodes = next;
    }
  }
  void try_reclaim(node* old_head) {
    if (threads_in_pop == 1) {
      node* nodes_to_delete = to_be_deleted.exchange(nullptr);
      if (!--threads_in_pop) {
        delete_nodes(nodes_to_delete);
      } else if(nodes_to_delete) {
        chain_pending_nodes(nodes_to_delete);
      }
      delete old_head;
    } else {
      chain_pending_node(old_head);
      --threads_in_pop;
    }
  }
  void chain_pending_nodes(node* nodes) {
    node* last = nodes;
    while (const node* next = last->next) {
      last = next;
    }
    chain_pending_nodes(nodes, last);
  }
  void chain_pending_nodes(node* first, node* last) {
    last->next = to_be_deleted;
    while(!to_be_deleted.compare_exchange_weak(last->next, first));
  }
  void chain_pending_node(node* n) {
    chain_pending_nodes(n, n);
  }
public:
  void push(const T& data) {
    const node* new_data = new node(data);
    new_data->next = head.load();
    while (!head.compare_exchange_weak(new_node->next, new_node));
  }
  std::shared_ptr<T> pop() {
    ++threads_in_pop;
    node* old_head = head.load();
    while(old_head && !head.compare_exchange_weak(old_head, old_head->next));
    std::shared_ptr<T> result;
    if (old_head) result.swap(old_head->data);
    try_reclaim(old_head);
    return result;
  }
};

#endif // __LOCK_FREE_STACK_H__