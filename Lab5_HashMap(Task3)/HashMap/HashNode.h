template <typename KEY, typename VALUE>
class HashNode {
public:
	HashNode(const KEY &newKey, const VALUE &newValue) {
		key = newKey;
		value = newValue;
		next = nullptr;
	}

	KEY getKey() const {
		return key;
	}

	VALUE getValue() const {
		return value;
	}

	HashNode *getNext() const {
		return next;
	}

	void setValue(VALUE value) {
		HashNode::value = value;
	}

	void setNext(HashNode *next) {
		HashNode::next = next;
	}
private:
	KEY key;
	VALUE value;
	// next bucket with the same key
	HashNode *next;
};