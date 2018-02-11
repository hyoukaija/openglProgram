
/*void HilbertOne(std::vector<glm::vec3> & g_vertex_buffer_data)
{
	glm::vec3 vertex;
	//start 
	vertex = glm::vec3(0, 0, 0);
	std::vector<glm::vec3> g_vertex_base = g_vertex_buffer_data;
	std::vector<glm::vec3>::iterator i;
	for (i = g_vertex_base.begin(); i != g_vertex_base.end(); i++)
	{

	}
	g_vertex_buffer_data.push_back(vertex);

	//up
	for (i = g_vertex_base.begin(); i != g_vertex_base.end(); i++)
	{

	}
	g_vertex_buffer_data.push_back(vertex);
	//back
	vertex = glm::vec3(-1.0f, 1.0f, 1.0f);
	g_vertex_buffer_data.push_back(vertex);
	//down
	vertex = glm::vec3(-1.0f, 1.0f, -1.0f);
	g_vertex_buffer_data.push_back(vertex);
	//right
	vertex = glm::vec3(1.0f, 1.0f, -1.0f);
	g_vertex_buffer_data.push_back(vertex);
	//up
	vertex = glm::vec3(1.0f, 1.0f, 1.0f);
	g_vertex_buffer_data.push_back(vertex);
	//foward
	vertex = glm::vec3(1.0f, -1.0f, 1.0f);
	g_vertex_buffer_data.push_back(vertex);
	//down
	vertex = glm::vec3(1.0f, -1.0f, -1.0f);
	g_vertex_buffer_data.push_back(vertex);
}
void Hilbert(std::vector<glm::vec3> & g_vertex_buffer_data, int n)
{
	glm::vec3 vertex;
	//start 
	vertex = glm::vec3(0, 0, 0);
	for (int j = 1; j <= n; j++)
	{
		std::vector<glm::vec3> g_vertex_base = g_vertex_buffer_data;
		std::vector<glm::vec3>::iterator i;
		for (i = g_vertex_base.begin(); i != g_vertex_base.end(); i++)
		{

		}
		g_vertex_buffer_data.push_back(vertex);

		//up
		for (i = g_vertex_base.begin(); i != g_vertex_base.end(); i++)
		{

		}
		g_vertex_buffer_data.push_back(vertex);
		//back
		vertex = glm::vec3(-1.0f, 1.0f, 1.0f);
		g_vertex_buffer_data.push_back(vertex);
		//down
		vertex = glm::vec3(-1.0f, 1.0f, -1.0f);
		g_vertex_buffer_data.push_back(vertex);
		//right
		vertex = glm::vec3(1.0f, 1.0f, -1.0f);
		g_vertex_buffer_data.push_back(vertex);
		//up
		vertex = glm::vec3(1.0f, 1.0f, 1.0f);
		g_vertex_buffer_data.push_back(vertex);
		//foward
		vertex = glm::vec3(1.0f, -1.0f, 1.0f);
		g_vertex_buffer_data.push_back(vertex);
		//down
		vertex = glm::vec3(1.0f, -1.0f, -1.0f);
		g_vertex_buffer_data.push_back(vertex);
	}

	*/