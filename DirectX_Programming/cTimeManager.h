#pragma once
class cTimeManager
{
private:
	static cTimeManager* m_pInstance;
	int m_nPrevTimStamp;
	int m_nElapsedTime;
	int m_nFrameCount;
	int m_nAccElapsedTime;
	int a;
	int m_nFPS;
	int m_nPrevFPS;
	int m_nStaticTime;
	cTimeManager();
	~cTimeManager();

public:
	void Init();
	void Update();

	static cTimeManager* GetInstance()
	{
		if (m_pInstance) return m_pInstance;

		m_pInstance = new cTimeManager;
		m_pInstance->Init();
		return m_pInstance;
	}
	float GetElapsedTime() { return m_nElapsedTime / 1000.0f; }
	int GetFPS() { return m_nFPS; }
	void Destroy();
	int GetStaticTime() { return m_nStaticTime; }
};