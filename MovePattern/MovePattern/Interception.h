


class Interception
{
public:
	Interception();
	~Interception();
private:
	float m_Vr;			// 相対速度
	float m_Sr;			// 相対距離
	float m_Tc;			// 接近時間

	float m_Sp;			// プレイヤーの現在座標
	float m_Vp;			// プレイヤーの移動ベクトル
	float m_Se;			// 敵の現在座標
	float m_Ve;			// 敵の移動ベクトル

	float m_point;		// 迎撃ポイント

protected:
	void Initialize();
	void Update();
};