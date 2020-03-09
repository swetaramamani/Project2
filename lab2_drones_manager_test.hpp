/*
Sweta Ramamani 20789147
Anusha Dey 20769485


*/

#ifndef DRONES_MANAGER_TEST
#define DRONES_MANAGER_TEST
#include "lab2_drones_manager.hpp"
//defining assertions for testing
#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

class DronesManagerTest {
public:
	// New empty list is valid
	bool test1() {
		DronesManager manager;
		ASSERT_TRUE(manager.get_size() == 0)
		ASSERT_TRUE(manager.empty())
		ASSERT_TRUE(manager.first == nullptr)
		ASSERT_TRUE(manager.last == nullptr)
	    return true;
	}
	
	//insert_front() and insert_back() on zero-element list
	bool test2() {
		DronesManager manager1, manager2;
		manager1.insert_front(DronesManager::DroneRecord(100));
		manager2.insert_back(DronesManager::DroneRecord(100));

		ASSERT_TRUE(manager1.first != nullptr && manager1.first == manager1.last)
		ASSERT_TRUE(manager2.first != nullptr && manager2.first == manager2.last)
		ASSERT_TRUE(manager1.first->prev == nullptr && manager1.last->next == nullptr)
		ASSERT_TRUE(manager2.first->prev == nullptr && manager2.last->next == nullptr)
		ASSERT_TRUE(manager1.select(0) == manager2.select(0) && manager1.select(0) == DronesManager::DroneRecord(100))		
	    return true;
	}
	
	//select() and search() work properly
	bool test3() {
        DronesManager m;
        DronesManager::DroneRecord t1(100);
        DronesManager::DroneRecord t2(101);
        DronesManager::DroneRecord nullRecord(0);

	    ASSERT_TRUE(m.select(0) == nullRecord);

	    m.insert_back(t1);
	    m.insert_back(t2);
	    m.insert_back(t1);
        m.insert_back(t2);

	    ASSERT_TRUE(m.get_size() == 4);
	    ASSERT_TRUE(m.select(0) == t1);
	    ASSERT_TRUE(m.select(m.get_size() + 10) == t2);
        ASSERT_TRUE(m.search(t1) == 0);
	    ASSERT_TRUE(m.search(t2) == 1);

	    return true;
	}
	
	//remove_front() and remove_back() on one-element list
	bool test4() {
		DronesManager m;
		DronesManager::DroneRecord r(100);

		ASSERT_TRUE(m.insert_front(r));
		ASSERT_TRUE(m.get_size() == 1);

		ASSERT_TRUE(m.remove_front());
		ASSERT_TRUE(m.empty());

		ASSERT_TRUE(m.first == nullptr && m.last == nullptr);

		ASSERT_TRUE(m.insert_front(r));
		ASSERT_TRUE(m.get_size() == 1);

		ASSERT_TRUE(m.remove_back());
		ASSERT_TRUE(m.empty());

		ASSERT_TRUE(m.first == nullptr && m.last == nullptr);
		return true;
	}
	
	//replace() and reverse_list() work properly
	bool test5() {
		DronesManager m;
		DronesManager::DroneRecord t1(100);
		DronesManager::DroneRecord t2(101);
		DronesManager::DroneRecord t3(102);

		m.insert_back(t1);
		m.insert_back(t2);
		m.insert_back(t3);

		ASSERT_TRUE(m.select(0) == t1);

		ASSERT_TRUE(m.replace(0, t2));
		ASSERT_TRUE(m.select(0) == t2);

		ASSERT_TRUE(m.replace(1, t1));
		ASSERT_TRUE(m.select(1) == t1);

		ASSERT_TRUE(m.reverse_list());
		ASSERT_TRUE(m.select(0) == t3);
		ASSERT_TRUE(m.select(1) == t1);
		ASSERT_TRUE(m.select(2) == t2);

		return true;
	}
	
	//insert_front() keeps moving elements forward
	bool test6() {
		DronesManager m;
		DronesManager::DroneRecord t1(100);
		DronesManager::DroneRecord t2(101);

		ASSERT_TRUE(m.insert_front(t2));
		ASSERT_TRUE(m.get_size() == 1);
		ASSERT_TRUE(m.insert_front(t1));
		ASSERT_TRUE(m.get_size() == 2);
		ASSERT_TRUE(m.select(0) == t1);
		ASSERT_TRUE(m.select(1) == t2);

		return true;
	}
	
	//inserting at different positions in the list
	bool test7() {
		DronesManager m;
		DronesManager::DroneRecord t1(100);
		DronesManager::DroneRecord t2(101);

		ASSERT_TRUE(m.insert(t1, 0));
		ASSERT_TRUE(m.insert(t1, 1));
		ASSERT_TRUE(m.get_size() == 2);
		ASSERT_TRUE(m.insert(t2, 2));
		ASSERT_TRUE(m.get_size() == 3);

		return true;
	}
	
	//try to remove too many elements, then add a few elements
	bool test8() {
	    DronesManager m;
	    DronesManager::DroneRecord t1(100);
        DronesManager::DroneRecord t2(200);

        m.insert_back(t1);
        ASSERT_TRUE(m.remove(0));

        ASSERT_FALSE(m.remove_front());
        ASSERT_FALSE(m.remove_back());
        ASSERT_FALSE(m.remove(0));

        ASSERT_TRUE(m.insert_front(t1));
        ASSERT_TRUE(m.insert_back(t2));

	    return true;
	}
	
	//lots of inserts and deletes, some of them invalid
	bool test9() {
        DronesManager m;
        DronesManager::DroneRecord t1(100);
        DronesManager::DroneRecord t2(200);

        ASSERT_FALSE(m.remove(0));
        ASSERT_TRUE(m.insert_back(t1));
        ASSERT_FALSE(m.insert(t2, 12));
        ASSERT_FALSE(m.insert(t2, 8));

        ASSERT_TRUE(m.remove(0));
        ASSERT_FALSE(m.remove(0));

        return true;
	}
	    	
	//inserts into an unsorted list, then sort the list
	bool test10() {
        DronesManagerSorted m;
        DronesManager::DroneRecord gtest(100);
        DronesManager::DroneRecord ntest(200);
        DronesManager::DroneRecord ztest(300);
        DronesManager::DroneRecord xtest(400);

        m.insert_front(gtest);
        m.insert_front(ntest);
        m.insert_front(ztest);
        m.insert_front(xtest);

        m.sort_asc();
        ASSERT_TRUE(m.is_sorted_asc());
        ASSERT_FALSE(m.is_sorted_desc());

        m.sort_desc();
        ASSERT_TRUE(m.is_sorted_desc());
        ASSERT_FALSE(m.is_sorted_asc());

        return true;
	}
	
	//insert and remove into sorted manager in ascending order
	bool test11() {
        DronesManagerSorted m;
        DronesManager::DroneRecord gtest(100);
        DronesManager::DroneRecord ntest(200);
        DronesManager::DroneRecord ztest(300);
        DronesManager::DroneRecord xtest(400);

        m.insert_sorted_asc(gtest);
        m.insert_sorted_asc(ntest);
        m.insert_sorted_asc(xtest);
        m.insert_sorted_asc(ztest);
        m.remove(0);

        ASSERT_TRUE(m.select(0) == gtest);
        ASSERT_TRUE(m.select(1) == ntest);
        ASSERT_TRUE(m.select(2) == xtest);

        return true;
	}
	
	//insert and remove into sorted manager in descending order
	bool test12() {
        DronesManagerSorted m;
        DronesManager::DroneRecord gtest(100);
        DronesManager::DroneRecord ntest(200);
        DronesManager::DroneRecord ztest(300);
        DronesManager::DroneRecord xtest(400);

        m.insert_sorted_desc(gtest);
        m.insert_sorted_desc(ntest);
        m.insert_sorted_desc(xtest);
        m.insert_sorted_desc(ztest);
        m.remove(0);

        ASSERT_TRUE(m.select(0) == ztest);
        ASSERT_TRUE(m.select(1) == ntest);
        ASSERT_TRUE(m.select(2) == gtest);

        return true;
	}
};

#endif
