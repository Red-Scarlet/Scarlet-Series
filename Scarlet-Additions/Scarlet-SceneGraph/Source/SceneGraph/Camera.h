#pragma once

#include <ScarletInterface.h>

namespace SceneGraph {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API Camera
	{
	public:
		Camera() = default;
		Camera(const Mathematics::Matrix4& _Projection)
			: m_ProjectionMatrix(_Projection) 
		{
		}
		virtual ~Camera() = default;

		const Mathematics::Matrix4& GetProjection() const { return m_ProjectionMatrix; }
	
	protected:
		Mathematics::Matrix4 m_ProjectionMatrix = Mathematics::Matrix4(1.0f);

	};

}