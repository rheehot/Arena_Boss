#include "ResourceManager.h"
#include <exception>
#include "IteratorFinder.h"
#include "Resource.h"

namespace ArenaBoss
{
	void ResourceManager::DeleteResource(const std::string& name)
	{
		const auto iter = IteratorFinder::FindSameIterator(resources, name);
		delete *iter;
		resources.erase(iter);
	}

	void ResourceManager::RegisterResource(Resource* resource)
	{
		const auto iter = IteratorFinder::
			FindLowerIterator(resources,resource->GetName());

		resources.emplace_back(std::move(resource));
		std::rotate(resources.rbegin(), resources.rbegin() + 1,
			std::reverse_iterator{ iter });
	}

	Resource* ResourceManager::FindResource(const std::string& name, const std::string& resourceName)
	{
		const auto resource = *IteratorFinder::FindSameIterator(resources, name);
		if (resource->ClassName() != resourceName)
			throw std::exception{ "No corresponding resource exists." };

		return resource;
	}
}