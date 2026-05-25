#pragma once

#include "lve_device.hpp"
#include "lve_game_object.hpp"
#include "lve_pipeline.hpp"

// std
#include <chrono>
#include <memory>
#include <vector>

namespace lve {
class SimpleRenderSystem {
 public:
  
  SimpleRenderSystem(LveDevice &device, VkRenderPass renderPass);
  ~SimpleRenderSystem();

  SimpleRenderSystem(const SimpleRenderSystem &) = delete;
  SimpleRenderSystem &operator=(const SimpleRenderSystem &) = delete;

    void renderGameObjects(VkCommandBuffer commandBuffer, std::vector<LveGameObject> &gameObjects, float deltaTime);

 private:
  void createPipelineLayout();
  void createPipeline(VkRenderPass renderPass);

  LveDevice& lveDevice;

  std::unique_ptr<LvePipeline> lvePipeline;
  VkPipelineLayout pipelineLayout;
  std::chrono::steady_clock::time_point lastFrameTime{std::chrono::steady_clock::now()};
};
}  // namespace lve