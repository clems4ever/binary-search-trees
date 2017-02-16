#ifndef BST_HPP
#define BST_HPP

namespace bst {

template<typename Key, typename Value>
class Node {
public:
  Node(const Key& mkey, const Value& mvalue) 
    : key(mkey), 
      value(mvalue), 
      leftNode(nullptr),
      rightNode(nullptr)
  {}
  Node(const Node& n) = delete;

  Key key;
  Value value;
  Node *leftNode;
  Node *rightNode;
};

template<typename Key, typename Value>
class Map {
public:
  Map() : m_size(0), rootNode(nullptr) {}

  class iterator {
  public:
    iterator(Node<Key, Value> *node) : m_node(node) {}
    iterator() : m_node(nullptr) {}
    iterator(const iterator& it) : m_node(it.m_node) {}

    bool operator==(const iterator& that) const {
      return m_node == that.m_node;
    }

    bool operator!=(const iterator& that) const {
      return !operator==(that);
    }

    Key& key() const { return m_node->key; }
    Value& value() const { return m_node->value; }
  private:
    Node<Key, Value>* m_node;
  };

  void insert(const std::pair<Key, Value>& p) {
    if(rootNode == nullptr) {
      rootNode = new Node<Key, Value>(p.first, p.second);
      m_size++;
      return;
    }

    Node<Key, Value> *current = rootNode;
    while(current != nullptr) {
      if(current->key < p.first) {
        if(current->leftNode == nullptr) {
          current->leftNode = new Node<Key, Value>(p.first, p.second);
          m_size++;
          return;
        }
        current = current->leftNode;
      }
      else if(current->key > p.first) {
        if(rootNode->rightNode == nullptr) {
          rootNode->rightNode = new Node<Key, Value>(p.first, p.second);
          m_size++;
          return;
        }
        current = current->rightNode;
      }
      else { return; }
    }
  }

  void removeNode(Node<Key, Value>* root) {
      if(root == nullptr) return;
 
      Node<Key, Value>* minNode = extractMinNode(root);
      root->key = minNode->key;
      root->value = minNode->value;
      delete minNode;
      m_size--;
      return;
  }

  Node<Key, Value>* extractMinNode(Node<Key, Value>* root) {
    if(root == nullptr) return nullptr;
    if(root != nullptr && root->leftNode == nullptr) return root;

    Node<Key, Value>* current = root;
    while(current->leftNode->leftNode != nullptr) {
      current = current->leftNode;
    }
    Node<Key, Value>* minNode = current->leftNode;
    current->leftNode = nullptr;
    return minNode;
  }

  void remove(const Key& key) {
    if(rootNode == nullptr) return;
    if(rootNode != nullptr && rootNode->key == key) {
      removeNode(rootNode);
      return;
    }

    Node<Key, Value> *current = rootNode;
    while(current != nullptr) {
      if(current->key < key) {
        current = current->leftNode;
      }
      else if(current->key > key) {
        current = current->rightNode;
      }
      else {
        removeNode(current);
      }
    }
  }

  const iterator begin() { return iterator(rootNode); }
  const iterator end() { return iterator(nullptr); }

  iterator get(const Key& key) {
    Node<Key, Value>* current = rootNode;
    while(current != nullptr) {
      if(key < current->key) {
        current = current->leftNode; 
      }
      else if(key > current->key) {
        current = current->rightNode; 
      }
      else {
        return iterator(current);
      }
    }
    return iterator();
  }

  size_t size() const { return m_size; }
private:
  size_t m_size;
  Node<Key, Value> *rootNode;
};

}

#endif

