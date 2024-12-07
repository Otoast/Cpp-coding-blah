# ifndef NODE
# define NODE

# include "TemperatureData.h"

struct Node {
	public:
		TemperatureData data;
		Node* next;

		Node();
		Node(std::string id, int year, int month, double temperature);
		bool operator<(const Node& b);

		Node(const Node& nToCopy);
		Node& operator=(const Node& rhs);
		virtual ~Node() {}
};

# endif
