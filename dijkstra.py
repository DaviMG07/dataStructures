import heapq as hpq

class Heap:
    def __init__(self: object) -> None:
        self.__pq = []
        return
    
    def push(self: object, key: any, priority: int | float) -> None:
        hpq.heappush(self.__pq, (key, priority))
        return
    
    def pop(self: object) -> tuple[any, int | float] | None:
        try:
            return hpq.heappop(self.__pq)
        except IndexError:
            return None
    
    def print(self: object) -> None:
        for element in self.__pq:
            print(f"({element[0]}, {element[1]})")
        return
    
    def empty(self:object) -> bool:
        return len(self.__pq) == 0


class Graph:
    def __init__(self: object) -> None:
        self.vertices: list[str] = []
        self.adj: dict[tuple[str, str], int] = {}
        return
    
    def add_edge(self: object, start: str, end: str, weight: int) -> None:
        if (start == end): return
        self.adj[(start, end)] = weight
        self.vertices.append(start)
        self.vertices.append(end)
        return
    
    def print(self: object) -> None:
        for vertex in self.adj:
            print(f"{vertex[0]} --({self.adj[vertex]})--> {vertex[1]}")
        return
    
    def dijkstra(self: object, src: str) -> tuple[dict[str, float], dict[str, str | None]]:
        distances: dict[str, float] = {
            vertex: float("inf") 
            for vertex in self.vertices
        }
        previous: dict[str, str | None] = {
            vertex: None 
            for vertex in self.vertices
        }
        pq: Heap = Heap()
        curr: str
        current_dist: int | float

        distances[src] = 0
        pq.push(src, distances[src])
        while (not pq.empty()):
            curr, current_dist = pq.pop()
            if current_dist > distances[curr]:
                continue

            for neighbor, weight in self.adj.items():
                if neighbor[0] != curr:
                    continue
                alt: float | int = distances[curr] + weight
                if alt >= distances[neighbor[1]]:
                    continue
                distances[neighbor[1]] = alt
                previous[neighbor[1]] = curr
                pq.push(neighbor[1], alt)
        return distances, previous
    
def main() -> None:
    g = Graph()
    g.add_edge("a", "b", 1.2)
    g.add_edge("b", "c", 3.1)
    g.add_edge("c", "d", 2.3)
    g.add_edge("d", "e", 3.4)
    print(g.dijkstra("a"))
    return

if __name__ == "__main__":
    main()
