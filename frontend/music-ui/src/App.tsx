import { useState, useEffect } from 'react'
import './App.css'

type Album = 
{
  title: string;
  artist: string;
  sizeMB: number;
};


function App() 
{
	const [count, setCount] = useState(0)
	const [albums, setAlbums] = useState<Album[]>([]);

	useEffect(() => {
    fetch("http://localhost:18080/albums")
		.then((res) => res.json())
		.then((data) => setAlbums(data))
		.catch((err) => console.error(err));
	}, []);

	return (
		<>
		<section id="center">
			<div>
				<h1>Get started</h1>
				<p>
					Edit <code>src/App.tsx</code> and save to test <code>HMR</code>
				</p>
			</div>
			<button
				type="button"
				className="counter"
				onClick={() => setCount((count) => count + 1)}
				>
				Count is {count}
			</button>
		</section>
		<div style={{ padding: "20px" }}>
		<h1>Music Library</h1>

		<table border={1} cellPadding={10}>
			<thead>
			<tr>
				<th>Title</th>
				<th>Artist</th>
				<th>Size (MB)</th>
			</tr>
			</thead>

			<tbody>
			{albums.map((album, i) => 
			(
				<tr key={i}>
				<td>{album.title}</td>
				<td>{album.artist}</td>
				<td>{album.sizeMB}</td>
				</tr>
			))}
			</tbody>
		</table>
		</div>
		</>
	)
}

export default App
