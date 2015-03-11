// 用于线程同步的类 QMutex, QReadWriteLock, QSemaphore, QWaitCondition
// QMutex类: 提供一种保护一个变量或者一段代码的方法, 这样就可以每次只让一个线程读取它;
	// 这个类提供了一个lock()函数来锁住互斥量(mutex), 如果互斥量是解锁的, 那么当前线程就立即占用并锁定它, 否则, 当前线程就会被阻塞, 直到掌握这个互斥量的线程对他解锁为止;