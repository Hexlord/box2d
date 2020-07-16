// MIT License

// Copyright (c) 2019 Erin Catto

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "test.h"
#include "imgui/imgui.h"

class CompoundShapes : public Test
{
public:
	CompoundShapes()
	{
		{
			b2BodyDef bd;
			bd.position.Set(0.0f, 0.0f);
			b2Body* body = m_world->CreateBody(&bd);

			b2EdgeShape shape;
			shape.SetTwoSided(b2Vec2(50.0f, 0.0f), b2Vec2(-50.0f, 0.0f));

			body->CreateFixture(&shape, 0.0f);
		}

		// Table 1
		{
			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.position.Set(-25.0f, 1.0f);
			m_table1 = m_world->CreateBody(&bd);

			b2PolygonShape top;
			top.SetAsBox(3.0f, 0.5f, b2Vec2(0.0f, 3.5f), 0.0f);

			b2PolygonShape leftLeg;
			leftLeg.SetAsBox(0.5f, 1.5f, b2Vec2(-2.5f, 1.5f), 0.0f);

			b2PolygonShape rightLeg;
			rightLeg.SetAsBox(0.5f, 1.5f, b2Vec2(2.5f, 1.5f), 0.0f);
			
			m_table1->CreateFixture(&top, 2.0f);
			m_table1->CreateFixture(&leftLeg, 2.0f);
			m_table1->CreateFixture(&rightLeg, 2.0f);
		}

		// Table 2
		{
			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.position.Set(-15.0f, 1.0f);
			m_table2 = m_world->CreateBody(&bd);

			b2PolygonShape top;
			top.SetAsBox(3.0f, 0.5f, b2Vec2(0.0f, 3.5f), 0.0f);

			b2PolygonShape leftLeg;
			leftLeg.SetAsBox(0.5f, 2.0f, b2Vec2(-2.5f, 2.0f), 0.0f);

			b2PolygonShape rightLeg;
			rightLeg.SetAsBox(0.5f, 2.0f, b2Vec2(2.5f, 2.0f), 0.0f);
			
			m_table2->CreateFixture(&top, 2.0f);
			m_table2->CreateFixture(&leftLeg, 2.0f);
			m_table2->CreateFixture(&rightLeg, 2.0f);
		}

		// Table 3
		{
			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.position.Set(-5.0f, 1.0f);
			m_table3 = m_world->CreateBody(&bd);

			b2Vec2 topVertices[] = {
				b2Vec2{-3.0f, 0.5f  + 3.5f},
				b2Vec2{-3.0f, -0.5f + 3.5f},
				b2Vec2{3.0f, -0.5f  + 3.5f},
				b2Vec2{3.0f, 0.5f   + 3.5f},
			};

			b2Vec2 topNormals[] = {
				b2Vec2{-1.0f, 0.0f},
				b2Vec2{0.0f, -1.0f},
				b2Vec2{1.0f, 0.0f},
				b2Vec2{0.0f, 1.0f},
			};

			bool topGhostEdges[] = {
				false,
				false,
				false,
				false,
			};

			b2PolygonShape top;
			top.Set(topVertices, topNormals, topGhostEdges, 4);

			b2Vec2 leftVertices[] = {
				b2Vec2{-0.5f - 2.5f, 1.5f  + 1.5f},
				b2Vec2{-0.5f - 2.5f, -1.5f + 1.5f},
				b2Vec2{0.5f  - 2.5f, -1.5f + 1.5f},
				b2Vec2{0.5f  - 2.5f, 1.5f  + 1.5f},
			};

			b2Vec2 leftNormals[] = {
				b2Vec2{-1.0f, 0.0f},
				b2Vec2{0.0f, -1.0f},
				b2Vec2{1.0f, 0.0f},
				b2Vec2{0.0f, 1.0f}, // shared with top
			};

			bool leftGhostEdges[] = {
				false,
				false,
				false,
				true,
			};

			b2PolygonShape leftLeg;
			leftLeg.Set(leftVertices, leftNormals, leftGhostEdges, 4);

			b2Vec2 rightVertices[] = {
				b2Vec2{-0.5f + 2.5f, 1.5f + 1.5f},
				b2Vec2{-0.5f + 2.5f, -1.5f + 1.5f},
				b2Vec2{0.5f  + 2.5f, -1.5f + 1.5f},
				b2Vec2{0.5f  + 2.5f, 1.5f + 1.5f},
			};

			b2Vec2 rightNormals[] = {
				b2Vec2{-1.0f, 0.0f},
				b2Vec2{0.0f, -1.0f},
				b2Vec2{1.0f, 0.0f},
				b2Vec2{0.0f, 1.0f}, // shared with top
			};

			bool rightGhostEdges[] = {
				false,
				false,
				false,
				true,
			};
			
			b2PolygonShape rightLeg;
			rightLeg.Set(rightVertices, rightNormals, rightGhostEdges, 4);

			m_table3->CreateFixture(&top, 2.0f);
			m_table3->CreateFixture(&leftLeg, 2.0f);
			m_table3->CreateFixture(&rightLeg, 2.0f);
		}

		// Spaceship 1
		{
			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.position.Set(5.0f, 1.0f);
			m_ship1 = m_world->CreateBody(&bd);

			b2Vec2 vertices[3];

			b2PolygonShape left;
			vertices[0].Set(-2.0f, 0.0f);
			vertices[1].Set(0.0f, 4.0f / 3.0f);
			vertices[2].Set(0.0f, 4.0f);
			left.Set(vertices, 3);

			b2PolygonShape right;
			vertices[0].Set(2.0f, 0.0f);
			vertices[1].Set(0.0f, 4.0f / 3.0f);
			vertices[2].Set(0.0f, 4.0f);
			right.Set(vertices, 3);
			
			m_ship1->CreateFixture(&left, 2.0f);
			m_ship1->CreateFixture(&right, 2.0f);
		}

		// Spaceship 2
		{
			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.position.Set(15.0f, 1.0f);
			m_ship2 = m_world->CreateBody(&bd);

			b2Vec2 vertices[3];

			b2PolygonShape left;
			vertices[0].Set(-2.0f, 0.0f);
			vertices[1].Set(1.0f, 2.0f);
			vertices[2].Set(0.0f, 4.0f);
			left.Set(vertices, 3);

			b2PolygonShape right;
			vertices[0].Set(2.0f, 0.0f);
			vertices[1].Set(-1.0f, 2.0f);
			vertices[2].Set(0.0f, 4.0f);
			right.Set(vertices, 3);

			m_ship2->CreateFixture(&left, 2.0f);
			m_ship2->CreateFixture(&right, 2.0f);
		}

		// Spaceship 3
		{
			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.position.Set(25.0f, 1.0f);
			m_ship3 = m_world->CreateBody(&bd);

			b2Vec2 leftVertices[] = {
				b2Vec2{0.0f, 4.0f / 3.0f},
				b2Vec2{0.0f, 4.0f},
				b2Vec2{-2.0f, 0.0f},
			};

			b2Vec2 leftNormals[] = {
				b2Cross(leftVertices[1] - leftVertices[0], 1.0f).Normalized(),
				b2Cross(leftVertices[2] - leftVertices[1], 1.0f).Normalized(),
				b2Cross(leftVertices[0] - leftVertices[2], 1.0f).Normalized(),
			};

			bool leftGhostEdges[] = {
				false,
				false,
				false,
			};

			b2PolygonShape left;
			left.Set(leftVertices, leftNormals, leftGhostEdges, 3);

			b2Vec2 rightVertices[] = {
				b2Vec2{2.0f, 0.0f},
				b2Vec2{0.0f, 4.0f},
				b2Vec2{0.0f, 4.0f / 3.0f},
			};

			b2Vec2 rightNormals[] = {
				b2Cross(rightVertices[1] - rightVertices[0], 1.0f).Normalized(),
				b2Cross(rightVertices[2] - rightVertices[1], 1.0f).Normalized(),
				b2Cross(rightVertices[0] - rightVertices[2], 1.0f).Normalized(),
			};

			bool rightGhostEdges[] = {
				false,
				true,
				false,
			};

			b2PolygonShape right;
			right.Set(rightVertices, rightNormals, rightGhostEdges, 3);

			m_ship3->CreateFixture(&left, 2.0f);
			m_ship3->CreateFixture(&right, 2.0f);
		}
	}

	void Spawn()
	{
		b2Body* tables[] = {
			m_table1,
			m_table2,
			m_table3,
		};

		for(b2Body* table : tables)
		{
			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.position = table->GetPosition();
			bd.angle = table->GetAngle();

			b2Body* body = m_world->CreateBody(&bd);

			b2PolygonShape box;
			box.SetAsBox(4.0f, 0.1f, b2Vec2(0.0f, 3.0f), 0.0f);

			body->CreateFixture(&box, 2.0f);
		}

		b2Body* ships[] = {
			m_ship1,
			m_ship2,
			m_ship3,
		};
		
		for (b2Body* ship : ships)
		{
			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.position = ship->GetPosition();
			bd.angle = ship->GetAngle();
			bd.gravityScale = 0.0f;

			b2Body* body = m_world->CreateBody(&bd);

			b2CircleShape circle;
			circle.m_radius = 0.5f;
			circle.m_p.Set(0.0f, 2.0f);

			body->CreateFixture(&circle, 2.0f);
		}
	}

	void UpdateUI() override
	{
		ImGui::SetNextWindowPos(ImVec2(10.0f, 100.0f));
		ImGui::SetNextWindowSize(ImVec2(200.0f, 100.0f));
		ImGui::Begin("Controls", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

		if (ImGui::Button("Spawn"))
		{
			Spawn();
		}

		ImGui::End();
	}

	static Test* Create()
	{
		return new CompoundShapes;
	}

	b2Body* m_table1;
	b2Body* m_table2;
	b2Body* m_table3;
	b2Body* m_ship1;
	b2Body* m_ship2;
	b2Body* m_ship3;
};

static int testIndex = RegisterTest("Examples", "Compound Shapes", CompoundShapes::Create);
