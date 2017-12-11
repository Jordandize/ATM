#ifndef _SERVICE_H_
#define _SERVICE_H_

//service interface
class Service
{
public:
	void service() { doService(); }
	string description() const { return doDescription(); }
	virtual ~Service() {};
private:
	virtual void doService() = 0;
	virtual string doDescription() const = 0;
};

#endif //_SERVICE_H_