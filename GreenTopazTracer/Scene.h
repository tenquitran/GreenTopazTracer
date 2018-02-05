#pragma once


namespace GreenTopazTracerApp
{
	// Contains object to ray trace.
	class Scene
	{
	public:
		Scene();

		virtual ~Scene();

	private:
		Scene(const Scene&) = delete;
		Scene& operator=(const Scene&) = delete;

	private:
		std::vector<GeometricObjectUPtr> m_objects;

		Color m_backgroundColor;
	};
}
